#pragma once
#include "Vector3.h"
#include "Shadow.h"
#include "Model.h"

class Drone
{
private:
	//shadow object for planar shadow
	Shadow droneShadow;
	//vectors for drone flight path
	Vector3 droneRotPoint, droneToMiddle, zeroDegrees;
	//drone position variables
	float droneX, droneZ, droneHeight, droneSpeed;
	//drone circle variables
	float droneT, droneRotate, droneRadius;
	//drone object
	Model drone;
	//shadow matrices
	float shadowMatrix[16];
	GLfloat floorMatrix[12] = { -1, 0, -1,
								-1, 0, 1,
								1, 0, 1,
								1, 0, -1 };

public:
	//constructor
	Drone();
	//light variables for spotlight
	GLfloat Light_Position_Sun[4] = { 0.5, 0.5, 0, 0 };
	GLfloat Drone_Light_Position[4] = { 0, 0, 0, 1 };

	void update(float dt, bool control, Vector3 cF);
	void render();

	Vector3 getPosition(); 
};

