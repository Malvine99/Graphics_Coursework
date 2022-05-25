#pragma once
#include "SOIL.h"
#include "Shape.h"


class Tree
{
private:
	//shape parts of tree
	Shape cone, sphere, stem, imposter;
	//texture variables
	GLuint bark, feather, flowers, baubles, imposterTex;

	//material variables
	GLfloat no_shiny[1] = { 0 };
	GLfloat low_shiny[1] = { 5 };
	GLfloat medium_shiny[1] = { 25 };
	GLfloat high_shiny[1] = { 100 };

	GLfloat emission_red[4] = {0.8, 0, 0, 0};
	GLfloat mat_diff_blue[4] = { 0, 0.3, 0.8, 1 };
	GLfloat mat_diff_orange[4] = { 0.5, 0.5, 0, 1 };
	GLfloat mat_diff_purple[4] = { 0.6, 0, 0.6, 1 };

	GLfloat lowSpec[4] = { 0.2, 0.2, 0.2, 1 };
	GLfloat highSpec[4] = { 1, 1, 1, 1 };
	GLfloat no_mat[4] = { 0, 0, 0, 0 };



public:
	void generateTree();
	void renderTree(float rotation);
};

