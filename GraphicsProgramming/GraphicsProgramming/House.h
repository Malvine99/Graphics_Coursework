#pragma once
#include "Shape.h"
#include "SOIL.h"

class House 
{

private:
	//house objects
	Shape wall, window, overDoor, roof, door, floor, gable, cctv, glass;
	//shelf objects
	Shape shelf, leg;
	//donut object
	Shape donut;
	//texture variables
	GLuint woodFloorTex, woodTex, woodVTex, mirrorTex, windowTex, doorTex;
	GLuint roofTex, brickTex, brickSmallTex;
	GLuint brownDonut, pinkDonut, whiteDonut;
	//material values for ceiling lights
	GLfloat emission_yellow[4] = { 0.3, 0.3, 0, 0 };
	GLfloat no_mat[4] = { 0, 0, 0, 0 };
	//dimensions for shelves
	float W, H, D;


public:
	void generateHouse();
	void generateShelf(float width, float height, float depth);

	void renderHouse(bool door, bool wall, bool wireframe);
	void renderInterior();
	void renderLights();
	void renderShelf(bool donuts);
	void renderShelfUnit(int height);
	void renderShelfWall(int height, int width);
	void renderDonutSet(int many);
};

