#pragma once
#include "Vector3.h"
#include "Shape.h"
#include "SOIL.h"

class Billboard
{
private:
	//quad that gets billboarded
	Shape quad;
	//up and forward vector to calculate rotation
	Vector3 up = { 0, 1, 0 };
	Vector3 forward = { 0, 0, 1 };
	//vector towards camera
	Vector3 toCam;
	//position
	Vector3 position;
	//angle to rotate by
	float angle;
	//dimesnions of the quad
	int W, H;
	//texture variable
	GLuint snowmanTex;

public:
	//default constructor 
	Billboard();
	//constructor to set dimensions
	Billboard(int width, int height, float x, float y, float z);

	void update(Vector3 camera);
	void render();
};

