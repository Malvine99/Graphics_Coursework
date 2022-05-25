// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Camera.h"
#include "House.h"
#include "Model.h"
#include "ShadowVolume.h"
#include "Drone.h"
#include "Billboard.h"

class Scene {

public:
	Scene(Input* in);
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions


	// For access to user input.
	Input* input;

	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

	GLboolean sun;
	Camera cam;
	bool door;

	//light definitions
	GLfloat Light_Ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat Light_Diffuse_White[4] = { 0.5, 0.5, 0.5, 1 };
	GLfloat Light_Diffuse_Yellow[4] = { 0.3f, 0.3f, 0.0f, 1 };
	GLfloat Light_Diffuse_Blue[4] = { 0, 0, 5, 1 };
	GLfloat Light_Diffuse_Red[4] = { 0.5, 0, 0, 1 };
	GLfloat Light_Specular[4] = { 0.5, 0.5, 0.5, 1 };
	GLfloat Light_Position_Ceiling1[4] = { 2, 5.7, -2, 1 };
	GLfloat Light_Position_Ceiling2[4] = { 8, 5.7, -8, 1 };
	GLfloat Drone_Light_Direction[3] = { 0, -1, 0 };
	GLfloat Light_Position_Tree[4] = { 12, 7.5, 3, 1 };
	GLfloat shadow_Light_Position[4] = { 5, 16, -16, 1 };
	float droneAttenuation, lightSpeed;

	//marker if wireframe is on
	bool wireframe;
	//objects for the surroundings
	Shape skyDome, ground, mirrorStencil, shadowLight;
	//surrounding textures
	GLuint skyTex, groundTex, donutTex;

	//objects 
	House house;
	Model treeStem, treeLeaves;
	ShadowVolume houseShadow;
	Drone drone;
	Billboard snowman;

	//further render variables
	float baubleRotation;

};

#endif