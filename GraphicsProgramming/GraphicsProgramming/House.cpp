#include "House.h"


void House::generateHouse() {

	//generate shapes
	wall.generateBox(10, 6, 0.1);
	window.generateBox(4, 6, 0.1);
	overDoor.generateBox(2, 2, 0.1);
	roof.generateBox(10, 7.1, 0.1);
	door.generateBox(2, 4, 0.1);
	floor.generateBox(9.999, 9.999, 0.1);
	gable.generateTrianglePlane(71, 10);
	cctv.generateDome(15);
	glass.generateQuad(2, 3);
	donut.generateTorus(3, 2, 30, 20);

	//load textures

	woodFloorTex = SOIL_load_OGL_texture(
		"gfx/woodfloor.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	roofTex = SOIL_load_OGL_texture(
		"gfx/roof.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	brickTex = SOIL_load_OGL_texture(
		"gfx/brick.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	brickSmallTex = SOIL_load_OGL_texture(
		"gfx/brickSmall.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	mirrorTex = SOIL_load_OGL_texture(
		"gfx/mirror.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	windowTex = SOIL_load_OGL_texture(
		"gfx/window.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	doorTex = SOIL_load_OGL_texture(
		"gfx/door.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	brownDonut = SOIL_load_OGL_texture(
		"gfx/brownDonut.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	whiteDonut = SOIL_load_OGL_texture(
		"gfx/whiteDonut.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	pinkDonut = SOIL_load_OGL_texture(
		"gfx/pinkDonut.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	generateShelf(2, 1, 0.5);
}

void House::generateShelf(float width, float height, float depth) {
	//store dimensions
	W = width; H = height; D = depth;
	//generate shapes
	leg.generateCylinder(20, height);
	shelf.generateBox(width, 0.1, depth);
	//load textures
	woodTex = SOIL_load_OGL_texture(
		"gfx/wood.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	woodVTex = SOIL_load_OGL_texture(
		"gfx/woodVert.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

}

void House::renderHouse(bool doorOpen, bool backWall, bool wireframe) {
	//make sure textures are on
	glEnable(GL_TEXTURE_2D);
	//enable ceiling lights, as they are disabled for the rest of the scene
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glColor3f(1, 1, 1);

	//render outer walls
	//bind outer wall texture
	glBindTexture(GL_TEXTURE_2D, brickTex);
	glPushMatrix();
		//left wall
		glTranslatef(0, 0, -10);
		glRotatef(-90, 0, 1, 0);
		wall.renderQuadShape();
	glPopMatrix();
	glPushMatrix();
		//right wall
		glTranslatef(10, 0, 0);
		glRotatef(90, 0, 1, 0);
		wall.renderQuadShape();
	glPopMatrix();
	//back wall
	//check if backwall needs to be rendered 
	//disabled for mirrored house becaus it blocks the view
	if (backWall) {
	glPushMatrix();
		//cut hole into back wall to see mirror through
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_EQUAL, 0, 1);
		glTranslatef(0, 0, -10);
		wall.renderQuadShape();
		glDisable(GL_STENCIL_TEST);
		//mirror on back wall
		glTranslatef(7.5, 0, 0.05);
		//bind mirror texture
		glBindTexture(GL_TEXTURE_2D, mirrorTex);
		//mirror is the same size as the door
		door.renderQuadShape();
	glPopMatrix();
	}

	//render roof
	//bind roof texture
	glBindTexture(GL_TEXTURE_2D, roofTex);
	glPushMatrix();
		glTranslatef(0, 6, -10);
		glRotatef(-90, 0, 1, 0);
		glRotatef(-45, 1, 0, 0);
		roof.renderQuadShape();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(10, 6, 0);
		glRotatef(90, 0, 1, 0);
		glRotatef(-45, 1, 0, 0);
		roof.renderQuadShape();
	glPopMatrix();

	//render gable
	//bind wood texture
	glBindTexture(GL_TEXTURE_2D, woodFloorTex);
	glPushMatrix();
		glTranslatef(5, 11, 0);
		glRotatef(-135, 0, 0, 1);
		gable.renderTriangleShape();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(5, 11, -10);
		glRotatef(180, 0, 1, 0);
		glRotatef(-135, 0, 0, 1);
		gable.renderTriangleShape();
	glPopMatrix();


	//render floor
	glPushMatrix();
		//translate slightly in z to avoid z-fighting
		glTranslatef(0, 0, 0.001);
		glRotatef(-90, 1, 0, 0);
		floor.renderQuadShape();
	glPopMatrix();
	//ceiling has no texture
	glDisable(GL_TEXTURE_2D);
	//render ceiling
	glPushMatrix();
		//translate slightly less in z to avoid z-fighting
		glTranslatef(0, 6, -9.999);
		glRotatef(90, 1, 0, 0);
		floor.renderQuadShape();
	glPopMatrix();

	//render interior
	renderInterior();

	//render lights&cctv to be seen through window
	//no front face (inside) so they don't intervene with the cctv view
	glPolygonMode(GL_FRONT, GL_POINT);
	renderLights();
	//check if wireframe mode is on
	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	//render front wall last, because it has transparency
	glColor3f(1, 1, 1);
	glPushMatrix();
		glPushMatrix();
			//render transparent quad in window position to give glass impression
			glDisable(GL_TEXTURE_2D);
			glColor4f(0, 0, 0.2, 0.35);
			glTranslatef(1, 2, 0.05);
			glass.renderQuadShape();
			glTranslatef(6, 0, 0);
			glass.renderQuadShape();
			glEnable(GL_TEXTURE_2D);
		glPopMatrix();
		//bind window texture 
		glBindTexture(GL_TEXTURE_2D, windowTex);
		glColor3f(1, 1, 1);
		window.renderQuadShape();
		glTranslatef(6, 0, 0);
		window.renderQuadShape();
		//bind overDoor texture
		glBindTexture(GL_TEXTURE_2D, brickSmallTex);
		glTranslatef(-2, 4, 0);
		overDoor.renderQuadShape();
		//bind door texture
		glBindTexture(GL_TEXTURE_2D, doorTex);
		glTranslatef(-0.01, -4, 0.01);
		//if door is open, rotate before rendering
		if (doorOpen) {
			glRotatef(-90, 0, 1, 0);
		}
		door.renderQuadShape();
	glPopMatrix();

	//cameras & ceiling lights
	renderLights();

	//disable ceiling lights again so they don't affect the outside
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);

}

void House::renderLights() {
	//lights don't have texture
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
		//move to ceiling height
		//first, because all of them need it
		glTranslatef(0, 6, 0);
		//downwards dome
		glRotatef(180, 1, 0, 0);
		//cameras
		glColor4f(0, 0, 0, 0.7);
		glPushMatrix();
			//move to right spot on ceiling
			glTranslatef(2, 0, 8);
			glPushMatrix();
				//give appropriate size
				glScalef(0.2, 0.2, 0.2);
				cctv.renderQuadShape();
			glPopMatrix();
			//move to right spot on ceiling
			glTranslatef(6, 0, -6);
			glPushMatrix();
				//give appropriate size
				glScalef(0.2, 0.2, 0.2);
				cctv.renderQuadShape();
			glPopMatrix();
		glPopMatrix();
		//light colour
		glColor3f(0.5, 0.5, 0);
		//set emission value
		glMaterialfv(GL_FRONT, GL_EMISSION, emission_yellow);
		glPushMatrix();
			//move to right spot on ceiling
			glTranslatef(2, 0, 2);
			glPushMatrix();
				//give appropriate size
				glScalef(0.3, 0.3, 0.3);
				cctv.renderQuadShape();
			glPopMatrix();
			//move to right spot on ceiling
			glTranslatef(6, 0, 6);
			glPushMatrix();
				//give appropriate size
				glScalef(0.3, 0.3, 0.3);
				cctv.renderQuadShape();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	//reset material value
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	//re-enable textures
	glEnable(GL_TEXTURE_2D);
}

void House::renderInterior() {

	//shelves
	glPushMatrix();
		//translate to position along wall
		glTranslatef(1, 0, -2);
		glRotatef(90, 0, 1, 0);
		renderShelfWall(8, 3);
	glPopMatrix();
	glPushMatrix();
		//translate to position along wall
		glTranslatef(1, 0, -9);
		renderShelfWall(8, 3);
	glPopMatrix();
	glPushMatrix();
		//translate to position in middle
		glTranslatef(5, 0, -3);
		glRotatef(90, 0, 1, 0);
		renderShelfWall(3, 2);
	glPopMatrix();
	glPushMatrix();
		//translate to position in middle
		glTranslatef(3, 0, -7);
		glRotatef(-90, 0, 1, 0);
		renderShelfWall(3, 2);
	glPopMatrix();

}

void House::renderShelf(bool donuts) {
	//render single shelf
	//bind wood texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, woodVTex);
	//render legs
	glPushMatrix();
	glTranslatef(0, 0, -0.45);
	//colour for legs
	glColor3f(0.3, 0.2, 0);
		glPushMatrix();
			glPushMatrix();
				//translate to right position under shelf
				glTranslatef(0.05, 0, -0.05);
				//scale to appropriate size
				glScalef(0.05, 0.5, 0.05);
				leg.renderQuadShape();
			glPopMatrix();
			//move to the back
			glTranslatef(0, 0, -D);
			glPushMatrix();
				//translate to right position under shelf
				glTranslatef(0.05, 0, 0.05);
				//scale to appropriate size
				glScalef(0.05, 0.5, 0.05);
				leg.renderQuadShape();
			glPopMatrix();
			//translate along width to other side
			glTranslatef(W, 0, 0);
			glPushMatrix();
				//translate to right position under shelf
				glTranslatef(-0.05, 0, 0.05);
				//scale to appropriate size
				glScalef(0.05, 0.5, 0.05);
				leg.renderQuadShape();
			glPopMatrix();
			//translate back to front
			glTranslatef(0, 0, D);
			glPushMatrix();
				//translate to right position under shelf
				glTranslatef(-0.05, 0, -0.05);
				//scale to appropriate size
				glScalef(0.05, 0.5, 0.05);
				leg.renderQuadShape();
			glPopMatrix();
		glPopMatrix();
		//render shelf
		//shelf colour
		glColor3f(0.6, 0.4, 0);
		glBindTexture(GL_TEXTURE_2D, woodTex);
		glPushMatrix();
			//translate up onto legs
			//to the back because the cube functions draws from the back corner
			glTranslatef(0, H/2, -D);
			shelf.renderQuadShape();
			glColor3f(1, 1, 1);
			//if donuts on this shelf, render a 4 by 4 set
			if (donuts) {
				renderDonutSet(4);
			}
		glPopMatrix();
	glPopMatrix();
}

void House::renderShelfUnit(int height) {
	//render height many shelves on top of each other
	for (int i = 0; i < height; i++) {
		glPushMatrix();
			glTranslatef(0, i * (H / 2), 0);
			renderShelf(i % 2 == 0);
		glPopMatrix();
	}
}

void House::renderShelfWall(int height, int width) {
	//render height by width shelves next to each other
	for (int i = 0; i < width; i++) {
		glPushMatrix();
			glTranslatef(i * W, 0, 0);
			renderShelfUnit(height);
		glPopMatrix();
	}
}

void House::renderDonutSet(int many)
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	//translate to start drawing at front of the shelf
	glTranslatef(0.25, 0.25, D);
	for (int j = 0; j < many; j++) {
		glPushMatrix();
		//render the different stacks in different colours
		switch (j) {
		case 0: glBindTexture(GL_TEXTURE_2D, brownDonut);
			break;
		case 1: glBindTexture(GL_TEXTURE_2D, whiteDonut);
			break;
		case 2: glBindTexture(GL_TEXTURE_2D, pinkDonut);
			break;
		case 3: glBindTexture(GL_TEXTURE_2D, whiteDonut);
			glColor3f(0.2, 0.7, 0.7);
			break;
		default:glBindTexture(GL_TEXTURE_2D, brownDonut);
			break;
		}
		for (int i = 0; i < many; i++) {

			glPushMatrix();
			//slightly tilt donuts
			glRotatef(-15, 1, 0, 0);
			//scale to appropriate size
			glScalef(0.03, 0.03, 0.03);
			donut.renderQuadShape();
			glPopMatrix();
			//translate back for next one, so they lean on each other
			glTranslatef(0, 0, -0.15);
		}
		glPopMatrix();
		//translate to the side for next stack
		glTranslatef(0.5, 0, 0);
	}
	glPopMatrix();
}
