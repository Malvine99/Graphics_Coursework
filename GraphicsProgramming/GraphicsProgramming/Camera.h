#pragma once
#include "Vector3.h"
#include "Input.h"
#include "glut.h"
#include "Drone.h"

class Camera
{
public:
	//constructors depending how specific you want to set up your camera
	Camera();
	Camera(Input* i);
	Camera(Input* i, float x, float y, float z);
	Camera(Input* i, float x, float y, float z, float P, float Ya, float R);
	
	void handleInput(float dt);
	void update(float dt, int windowWidth, int windowHeight, Drone *d);

	//position
	void setPosition(float x, float y, float z) { position.set(x, y, z); };
	void setPosition(Vector3 v) { position.set(v.x, v.y, v.z); };
	Vector3 getPosition() { return position; };
	//forward
	void setForward(float x, float y, float z) { forward.set(x, y, z); };
	Vector3 getForward() { return forward; };
	//look at
	void setLook(float x, float y, float z) { look.set(x, y, z); };
	Vector3 getLook() {	return look; };
	//up
	void setUp(float x, float y, float z) { up.set(x, y, z); };
	Vector3 getUp() { return up; };
	//right
	Vector3 getRight() { return right; };
	//Pitch, Yaw, Roll
	void setPitch(float x) { Pitch = x; };
	float getPitch() { return Pitch; };
	void setYaw(float y) { Yaw = y; };
	float getYaw() { return Yaw; };
	void setRoll(float z) { Roll = z; };
	float getRoll() { return Roll; };
	//camera states
	enum camState { free, cctv1, cctv2, droneC };
	camState which;

protected:
	Input* input;
	//mouse variables
	float mouseDX, mouseDY, centreX, centreY;
	//state markers (mouse en-/disabled, if camera needs update)
	bool mouse, moved, direction;
	float camSpeed;

	//vectors
	Vector3 position;
	Vector3 forward;
	Vector3 look;
	Vector3 up;
	Vector3 right;
	//rotation angles
	float Pitch, Yaw, Roll;

	//movement functions
	void moveBackFront(float direction);
	void moveSide(float direction);
	void rotateYaw(float direction);
	void rotatePitch(float direction);

};

