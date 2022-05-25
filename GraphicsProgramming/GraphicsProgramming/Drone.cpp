#include "Drone.h"

Drone::Drone()
{
	//load model
	drone.load("models/drone.obj", "models/Drone_Diff.jpg");
	//initialise variables
	droneSpeed = 0.1;
	droneRadius = 8;
	droneRotPoint = { 5, 13, -5 };
	droneHeight = droneRotPoint.y;
	Drone_Light_Position[1] = droneHeight;
	droneX = 5;
	droneZ = 3;
	zeroDegrees.x = 1;
}

void Drone::update(float dt, bool control, Vector3 cF)
{
	//update drone position
	if (!control) {
		//calculate vector from drone to centre of circle
		droneToMiddle.x = (droneRotPoint.x - droneX);
		droneToMiddle.z = (droneRotPoint.z - droneZ);

		//move to right height
		if (droneHeight < (droneRotPoint.y + 0.1) && (droneHeight > droneRotPoint.y - 0.1)) {
			droneHeight = droneRotPoint.y;
		}
		else if (droneHeight > droneRotPoint.y) {
			droneHeight -= 5*(droneSpeed * dt);
		}
		else if (droneHeight < droneRotPoint.y) {
			droneHeight += 5*(droneSpeed * dt);
		}
		//move x and z
		if (droneToMiddle.length() < (droneRadius - 0.1)) {
			//if drone on the inside of circle
			//fly towards circle, away from centre in straight line
			droneToMiddle.normalise();
			droneX -= droneToMiddle.x * dt;
			droneZ -= droneToMiddle.z * dt;
			//update angle of the circle the drone is on
			if (droneZ > droneRotPoint.z) {
				droneT = 3.1415 - droneToMiddle.angleR(zeroDegrees);
			}
			else {
				droneT = 3.1415 + droneToMiddle.angleR(zeroDegrees);
			}

		}
		else if (droneToMiddle.length() <= droneRadius) {
			//if on circle, fly in circle
			if (droneT < 2 * 3.1415) {
				//increase angle
				droneT += droneSpeed * dt;
				//move to point on circle
				droneX = (cosf(droneT) * droneRadius) + droneRotPoint.x;
				droneZ = (sinf(droneT) * droneRadius) + droneRotPoint.z;
				//rotate drone
				droneRotate += 10 * dt;
			}
			else {
				//reset Theta to not go over 360 degrees
				droneT = 0;
			}

		}
		//if distance from drone to centre > radius 
		//(drone not on circle)
		else if (droneToMiddle.length() > droneRadius) {
			//fly towards centre in straight line
			droneToMiddle.normalise();
			droneX += droneToMiddle.x * dt;
			droneZ += droneToMiddle.z * dt;
			//update angle of the circle the drone is on
			if (droneZ > droneRotPoint.z) {
				droneT = 3.1415 - droneToMiddle.angleR(zeroDegrees);
			}
			else {
				droneT = 3.1415 + droneToMiddle.angleR(zeroDegrees);
			}
		}
	}

	else if (control) {
		//if camera is following drone
		//have drone fly in direction you're looking
		droneX += 3*(cF.x * dt);
		droneHeight += 3*(cF.y * dt);
		droneZ += 3*(cF.z * dt);
	}
}

void Drone::render()
{
	//render drone shadow
	//first so it doesn't go over other objects as it has no depth test
	droneShadow.generateShadowMatrix(shadowMatrix, Light_Position_Sun, floorMatrix);
	glPushMatrix();
		//underneath drone position
		glTranslatef(droneX, 0, droneZ);

		//no depth test so it disappears behind objects
		glDisable(GL_DEPTH_TEST);
		//not affected by light
		glDisable(GL_LIGHTING);
		//shadow has no texture
		glDisable(GL_TEXTURE_2D);
		//set to dark grey colour
		glColor3f(0.1, 0.1, 0.1);
		//calculate planar projection
		glMultMatrixf((GLfloat*)shadowMatrix);
		//rotate the same as actual drone
		glRotatef(-droneRotate, 0, 1, 0);
		//make bigger because the actual shadow is tiny
		glScalef(20, 20, 20);
		//render shadow
		drone.render();
	glPopMatrix();
		//re-enable everything
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);


		glColor3f(1, 1, 1);

	//render drone
	glPushMatrix();
		//translate to drone position 
		glTranslatef(droneX, droneHeight, droneZ);
		//rotate drone
		glRotatef(-droneRotate, 0, 1, 0);
		//set light to drone position
		Drone_Light_Position[0] = droneX;
		Drone_Light_Position[1] = droneHeight;
		Drone_Light_Position[2] = droneZ;
		//scale because the model is tiny
		glScalef(20, 20, 20);
		//render actual drone
		drone.render();
	glPopMatrix();

}

Vector3 Drone::getPosition()
{
	//get drone's position
	Vector3 pos = { droneX, droneHeight, droneZ };
	return pos;
}


