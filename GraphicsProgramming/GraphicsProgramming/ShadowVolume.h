#pragma once
#include "Shape.h"
#include "Shadow.h"
#include "Tree.h"
#include <vector>

class ShadowVolume
{

private:
	//texture for floor
	GLuint grTex;
	//objects for floor and first wall
	Shape  shadowWall;
	//vertex arrays for shadow casting walls and shadowvolume
	std::vector<float> shadowVolQ;
	std::vector<float> gable = {
		0, 6, 0,
		10, 6, 0,
		5, 11, 0
	};
	std::vector<float> rightWall = {
		10, 6, 0,
		10, 0, 0,
		10, 0, -10,
		10, 6, -10
	};
	std::vector<float> leftWall = {
		0, 6, -10,
		0, 0, -10,
		0, 0, 0,
		0, 6, 0
	};

public:
	ShadowVolume();

	//tree & floor object. Public so it can be rendered in scene for transparency
	Tree tree;
	Shape floor;

	void generateShadowVolume();
	void renderHouseShadows(GLfloat lightPos[4], float baubleRotation);
	void renderShadowVolume();
};

