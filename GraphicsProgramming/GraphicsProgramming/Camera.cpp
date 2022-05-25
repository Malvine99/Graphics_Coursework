#include "Camera.h"

Camera::Camera()
{
	//initialise variables
	camSpeed = 15;
	mouse = false;
	moved = true;
	direction = false;
}

Camera::Camera(Input *i) {
	//initialise variables
	input = i;
	position.set(0, 0, 6);
	Pitch = 0;
	Yaw = 0;
	Roll = 0;
	which = free;
	camSpeed = 15;
	mouse = false;
	moved = true;
	direction = false;
};

Camera::Camera(Input* i, float x, float y, float z) {
	//initialise variables
	input = i;
	position.set(x, y, z);
	Pitch = 0;
	Yaw = 0;
	Roll = 0;
	which = free;
	camSpeed = 15;
	mouse = false;
	moved = true;
	direction = false;
};

Camera::Camera(Input* i, float x, float y, float z, float P, float Ya, float R) {
	//initialise variables
	input = i;
	position.set(x, y, z);
	Pitch = P;
	Yaw = Ya;
	Roll = R;
	which = free;
	camSpeed = 15;
	mouse = false;
	moved = true;
	direction = false;
}

void Camera::handleInput(float dt)
{
	//camera movement
	///enabled depending on state
	switch (which) {
	case free: {
		//forward 
		if (input->isKeyDown('w')) {
			moveBackFront(camSpeed * dt);
			moved = true;
		}//backward
		if (input->isKeyDown('s')) {
			moveBackFront(-camSpeed * dt);
			moved = true;
		}
		//right
		if (input->isKeyDown('d')) {
			moveSide(camSpeed * dt);
			moved = true;
		} //left
		if (input->isKeyDown('a')) {
			moveSide(-camSpeed * dt);
			moved = true;
		}
		//rotation keyboard
		//rotate up 
		if (input->isKeyDown('i')) {
			rotatePitch(3 * camSpeed * dt);
			moved = true;
		} //rotate down
		else if (input->isKeyDown('k')) {
			rotatePitch(-3 * camSpeed * dt);
			moved = true;
		}
		//rotate left 
		if (input->isKeyDown('j')) {
			rotateYaw(-3 * camSpeed * dt);
			moved = true;
		} //rotate right
		else if (input->isKeyDown('l')) {
			rotateYaw(3 * camSpeed * dt);
			moved = true;
		}
		//only break if mouse is disabled
		if (!mouse) { break; }
	case droneC:
		//rotation mouse
		//calculate distance from mouse position to centre of window
		mouseDX = centreX - input->getMouseX();
		mouseDY = centreY - input->getMouseY();

		if (mouseDX != 0) {
			//rotate according to mouse distance
			rotateYaw(2 * -mouseDX * dt);
			//set mouse to centre of window
			glutWarpPointer(centreX, centreY);
			//marker for camera variables to be updated
			moved = true;
		}
		if (mouseDY != 0) {
			//rotate according to mouse distance
			rotatePitch(2 * mouseDY * dt);
			//set mouse to centre of window
			glutWarpPointer(centreX, centreY);
			//marker for camera variables to be updated
			moved = true;
		}
		break;
	}
	};

	//toggle mouse camera
	if (input->isLeftMouseButtonPressed()) {
		input->setLeftMouseButton(false);
		if (!mouse) {
			//hide cursor when mouse control is enabled
			glutSetCursor(GLUT_CURSOR_NONE);
			mouse = true;
		}
		else {
			//show cursor when mouse control is disabled
			glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
			mouse = false;
		}
	}
	//camera states
	//free camera
	if (input->isKeyDown('1')) {
		which = free;
		input->SetKeyUp('1');
		moved = true;
	}
	//cctv looking at front
	if (input->isKeyDown('2')) {
		which = cctv1;
		input->SetKeyUp('2');
		//position inside CCTV dome
		setPosition(2, 5.92, -8);
		//start direction to look at
		setPitch(-40);
		setYaw(180);
		moved = true;
	}
	//cctv looking at back
	if (input->isKeyDown('3')) {
		which = cctv2;
		input->SetKeyUp('3');
		//position inside CCTV dome
		setPosition(8, 5.92, -2);
		//start direction to look at
		setPitch(-40);
		setYaw(0);
		moved = true;
	}
	//follow drone
	if (input->isKeyDown('4')) {
		which = droneC;
		input->SetKeyUp('4');
		moved = true;
	}

}

void Camera::update(float dt, int windowWidth, int windowHeight, Drone *d) {
	float cosP, cosY, cosR;
	float sinP, sinY, sinR;

	if (moved) {
		//recalculate camera vectors
		//only if the camera has been moved 
		cosP = cosf(Pitch * 3.1415 / 180);
		cosY = cosf(Yaw * 3.1415 / 180);
		cosR = cosf(Roll * 3.1415 / 180);
		sinP = sinf(Pitch * 3.1415 / 180);
		sinY = sinf(Yaw * 3.1415 / 180);
		sinR = sinf(Roll * 3.1415 / 180);

		forward.x = sinY * cosP;
		forward.y = sinP;
		forward.z = cosP * -cosY;

		look.x = position.x + forward.x;
		look.y = position.y + forward.y;
		look.z = position.z + forward.z;

		up.x = -cosY * sinR - sinY * sinP * cosR;
		up.y = cosP * cosR;
		up.z = -sinY * sinR - sinP * cosR * -cosY;

		right = forward.cross(up);
		
		moved = false;
	}

	//update depending on which state the camera is in
	switch (which) {
	//if on cctv, update yaw to rotate
	case cctv1:
		//check if space is being pressed to halt movement
		if (!input->isKeyDown(32)) {
			//check which direction to rotate based on angle
			if (getYaw() >= 180) {
				direction = false;
			}
			else if (getYaw() <= 90) {
				direction = true;
			}
			//update Yaw accordingly to rotate left/right
			if (!direction) {
				setYaw(getYaw() - camSpeed * dt);
			}
			else if (direction) {
				setYaw(getYaw() + camSpeed * dt);
			}
			moved = true;
		}
		break;
	case cctv2:
		//check if space is being pressed to halt movement
		if (!input->isKeyDown(32)) {
			//check which direction to rotate based on angle
			if (getYaw() >= 0) {
				direction = false;
			}
			else if (getYaw() <= -90) {
				direction = true;
			}
			//update Yaw accordingly to rotate left/right
			if (!direction) {
				setYaw(getYaw() - camSpeed * dt);
			}
			else if (direction) {
				setYaw(getYaw() + camSpeed * dt);
			}
			moved = true;
		}
		break;
	case droneC:
		//set camera above the drone
		setPosition(d->getPosition().x, d->getPosition().y + 1, d->getPosition().z);
		moved = true;
		break;
	}

	//coordinates to force mouse in the middle
	centreX = windowWidth / 2;
	centreY = windowHeight / 2;

}

void Camera::moveBackFront(float direction) {
	//move along forward vector
	//direction decides positive or negative value
	forward.scale(direction);
	setPosition(getPosition() + getForward());
}

void Camera::moveSide(float direction) {
	//move along right vector
	//direction decides positive or negative value
	right.scale(direction);
	setPosition(getPosition() + getRight() );
}

void Camera::rotateYaw(float direction) {	
	//rotate along Yaw
	//direction decides positive or negative value
	setYaw(getYaw() + direction);
}

void Camera::rotatePitch(float direction) {
	//rotate along Pitch
	//direction decides positive or negative value
	setPitch(getPitch() + direction);
}