#include "Billboard.h"

Billboard::Billboard() {

}

Billboard::Billboard(int width, int height, float x, float y, float z)
{
	//store width and height
	W = width;
	H = height;
	//generate object
	quad.generateQuad(width, height);
	//load texture
	snowmanTex = SOIL_load_OGL_texture(
		"gfx/snowman.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	//initialise position
	position = { x, y, z };
}

void Billboard::update(Vector3 camera)
{
	//calculate vector towards camera
	toCam = camera - position;
	//calculate angle
	angle = toCam.angleD(forward);
	//calculate if negative or positive angle
	if (forward.cross(toCam).y < 0) {
		angle = -angle;
	}
}

void Billboard::render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, snowmanTex);
	glPushMatrix();
		//translate to right position
		glTranslatef(position.x, position.y, position.z);
		//rotate by angle towards camera
		glRotatef(angle, 0, 1, 0);
		//move by half its width to make rotation look like its around the centre of the object
		glTranslatef(-(W / 2), 0, 0);
		//render object
		quad.renderQuadShape();
	glPopMatrix();

}
