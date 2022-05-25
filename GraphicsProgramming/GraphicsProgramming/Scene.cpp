#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
		
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.2f, 0.7f, 0.7f, 1.0f);				// Deep Sea Turqoise Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	//normalize all normals to avoid issues with them scaling
	glEnable(GL_NORMALIZE);

	// Other OpenGL / render setting should be applied here.
	//load textures
	skyTex = SOIL_load_OGL_texture(
		"gfx/skybox.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	groundTex = SOIL_load_OGL_texture(
		"gfx/grass.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	//enable necessary OpenGL functions
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	//generate objects
	cam = Camera(input, 0, 3, 6);
	skyDome.generateDome(30);
	ground.generateCone(0, 1, 30);
	house.generateHouse();
	mirrorStencil.generateQuad(1.6, 3.6);
	houseShadow.generateShadowVolume();
	shadowLight.generateSphere(30);
	snowman = Billboard(2, 4, -5, 0, 6);
	//load models
	treeStem.load("models/tree/MapleTreeStem.obj", "models/tree/maple_bark.png");
	treeLeaves.load("models/tree/MapleTreeLeaves.obj", "models/tree/maple_leaf.png");

	// Initialise scene variables
	baubleRotation = 0;
	droneAttenuation = 0.2;
	lightSpeed = 50;
	wireframe = false;
	door = true;
}

void Scene::handleInput(float dt)
{
	// Handle user input
	cam.handleInput(dt);

	//turn off sunlight
	if (input->isKeyDown('z')) {
		//check if light is on
		glGetBooleanv(GL_LIGHT0, &sun);
		if (GL_TRUE == sun) {
			glDisable(GL_LIGHT0);
		}
		else {
			glEnable(GL_LIGHT0);
		}
		input->SetKeyUp('z');
	} 
	//toggle wireframe
	if (input->isKeyDown('q')) {
		if (!wireframe) {
			wireframe = true;
		}
		else {
			wireframe = false;
		}
		input->SetKeyUp('q');
	}
	//open/close door
	if (input->isKeyDown('x')) {
		input->SetKeyUp('x');
		if (door) {
			door = false;
		}
		else {
			door = true;
		}
	}

	//control shadow volume light
	if (input->isKeyDown('v')) {
		//left
		shadow_Light_Position[0] -= lightSpeed * dt;
		input->SetKeyUp('v');
	}
	if (input->isKeyDown('b')) {
		//right
		shadow_Light_Position[0] += lightSpeed * dt;
		input->SetKeyUp('b');
	}
	if (input->isKeyDown('r')) {
		//back
		shadow_Light_Position[2] -= lightSpeed * dt;
		input->SetKeyUp('r');
	}
	if (input->isKeyDown('f')) {
		//front
		shadow_Light_Position[2] += lightSpeed * dt;
		input->SetKeyUp('f');
	}


	//change drone light attenuation
	if (input->isKeyDown('t')) {
		//increase
		droneAttenuation += 0.05;
		input->SetKeyUp('t');
	}
	if (input->isKeyDown('g')) {
		//decrease
		droneAttenuation -= 0.05;
		input->SetKeyUp('g');
	}

}

void Scene::update(float dt)
{
	// update scene related variables.

	//update camera
	cam.update(dt, width, height, &drone);

	//wireframe
	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (!wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	//update drone position
	drone.update(dt, cam.which == Camera::camState::droneC, cam.getForward());

	//rotate baubles
	baubleRotation += 50 * dt;

	//update snowman rotation
	snowman.update(cam.getPosition());

	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z, cam.getLook().x, cam.getLook().y, cam.getLook().z, cam.getUp().x, cam.getUp().y, cam.getUp().z);

#pragma region lights
	//setup lights
	//ambient & directional light
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse_White);
	glLightfv(GL_LIGHT0, GL_POSITION, drone.Light_Position_Sun);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light_Specular);
	//ceiling light 1, yellow
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse_Yellow);
	glLightfv(GL_LIGHT1, GL_EMISSION, Light_Diffuse_Yellow);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position_Ceiling1);
	//ceiling light 2, yellow
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse_Yellow);
	glLightfv(GL_LIGHT2, GL_EMISSION, Light_Diffuse_Yellow);
	glLightfv(GL_LIGHT2, GL_POSITION, Light_Position_Ceiling2);
	//red light on top of christmas tree
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Light_Diffuse_Red);
	glLightfv(GL_LIGHT3, GL_EMISSION, Light_Diffuse_Red);
	glLightfv(GL_LIGHT3, GL_POSITION, Light_Position_Tree);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.05);
	glEnable(GL_LIGHT3);
	//drone spot light
	glLightfv(GL_LIGHT4, GL_DIFFUSE, Light_Diffuse_Blue);
	glLightfv(GL_LIGHT4, GL_POSITION, drone.Drone_Light_Position);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, Drone_Light_Direction);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 30.0f);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 40);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, droneAttenuation);
	glEnable(GL_LIGHT4);
	//shadow casting point light
	glLightfv(GL_LIGHT5, GL_DIFFUSE, Light_Diffuse_White);
	glLightfv(GL_LIGHT5, GL_POSITION, shadow_Light_Position);
	glEnable(GL_LIGHT5);

#pragma endregion lights
	// Render geometry/scene here -------------------------------------
#pragma region Sky&stencil


	//skydome and ground
	glPushMatrix();	
		//translate to camera position
		glTranslatef(cam.getPosition().x, cam.getPosition().y - 0.2, cam.getPosition().z);
		//disable depth test so it gets covered by things rendered after
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, skyTex);
		skyDome.renderQuadShape();
		glBindTexture(GL_TEXTURE_2D, groundTex);
		ground.renderTriFanShape();
	glPopMatrix();

	//stencil for mirror
	//disable drawing
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	//enable stencil test, fill with 1 where the quad is
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	//change stencil
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//make backface invisible
	glPolygonMode(GL_BACK, GL_POINT);
	//draw stencil surface
	glPushMatrix();
		glTranslatef(7.7, 0.05, -9.89);
		mirrorStencil.renderQuadShape();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	//re-enable drawing
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	//check to find the 1s
	glStencilFunc(GL_EQUAL, 1, 1);
	//keep stencil as is
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//check for wireframe to see what to reset polygonmode to
	if (!wireframe) {
		glPolygonMode(GL_BACK, GL_FILL);
	}
	else {
		glPolygonMode(GL_BACK, GL_LINE);
	}
#pragma endregion

	//floor not affected by stencil
	glDisable(GL_STENCIL_TEST);	
	glPushMatrix();
		//lit floor object around/under house
		//rendered first so it doesn't cover the drone shadow
		//moved down slightly to prevent z-fighting
		glTranslatef(-10, -0.01, 45);
		glRotatef(-90, 1, 0, 0);
		glColor3f(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, groundTex);
		houseShadow.floor.renderQuadShape();
	glPopMatrix();

	//render drone, this includes the shadow
	drone.render();

	//mirrored house
	//not affected by blue spotlight
	//rendered after drone so the shadow doesn't show up in the mirror
	//stencil test enabled to only be seen through the mirror
	glEnable(GL_STENCIL_TEST);
	//not affected by the red light and the shadow casting light
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glPushMatrix();
		//flip house in z
		glScalef(1, 1, -1);
		//move to position behind house
		glTranslatef(0, 0, 20);
		//render house without back wall
		house.renderHouse(door, false, wireframe);
	glPopMatrix();
	//disable stencil test for following objects
	glDisable(GL_STENCIL_TEST);
	//re-enable lights
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);

	//render tree without shadow so it can be seen from inside the house
	houseShadow.tree.renderTree(baubleRotation);

	//when roughly inside the house, render snowman first so it can be seen through the window
	if (cam.getPosition().z < 0 && cam.getPosition().x > 0) {
		snowman.render();
	}

	//render house, with back wall
	house.renderHouse(door, true, wireframe);

	//clear stencil buffer to prevent overlapping with shadow volume stencil
	glClear(GL_STENCIL_BUFFER_BIT);

	glPushMatrix();
		//give light purple colour
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.5, 0, 0.5);
		//translate to shadow casting light position
		glTranslatef(shadow_Light_Position[0], shadow_Light_Position[1], shadow_Light_Position[2]);
		shadowLight.renderQuadShape();
		//re-enable textures
		glEnable(GL_TEXTURE_2D);
	glPopMatrix();

	//render model tree
	glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(-8, 0, -4);
		treeStem.render();
		treeLeaves.render();
	glPopMatrix();

	//render volume shadow of house walls
	houseShadow.renderHouseShadows(shadow_Light_Position, baubleRotation);

	//when definitely outside the house render snowman last so its transparency doesn't mess with the other objects.
	if (cam.getPosition().z > 0 || cam.getPosition().x < 0) {
		snowman.render();
	}
	

	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	
}

// Calculates FPS
void Scene::calculateFPS()
{

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
