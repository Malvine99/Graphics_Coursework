#include "ShadowVolume.h"

ShadowVolume::ShadowVolume()
{
}

void ShadowVolume::generateShadowVolume()
{
	grTex = SOIL_load_OGL_texture(
		"gfx/grass.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	//generate procedural objects
	shadowWall.generateQuad(10, 6);
	floor.generatePlane(30, 60, 1);
	tree.generateTree();
}

void ShadowVolume::renderHouseShadows(GLfloat lightPos[4], float baubleRotation)
{

	glPushMatrix();

		//create first shadow volume
		shadowVolQ = Shadow::buildShadowVolume(lightPos, shadowWall.getVerts());
		//disable drawing
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

		//render floor
		glPushMatrix();
			glDisable(GL_TEXTURE_2D);
			glTranslatef(-10, 0, 45);
			glRotatef(-90, 1, 0, 0);
			floor.renderQuadShape();
		glPopMatrix();
		//render christmas tree
		tree.renderTree(baubleRotation);

		//render shadow volume 
		renderShadowVolume();
		//create and render volumes for other walls
		shadowVolQ = Shadow::buildShadowVolume(lightPos, gable);
		renderShadowVolume();
		if (lightPos[0] < 10) {
			shadowVolQ = Shadow::buildShadowVolume(lightPos, rightWall);
			renderShadowVolume();
		}
		if (lightPos[0] > 0) {
			shadowVolQ = Shadow::buildShadowVolume(lightPos, leftWall);
			renderShadowVolume();
		}
		glDisableClientState(GL_VERTEX_ARRAY);

		//re-enable drawing, depth mask 
		glDepthMask(GL_TRUE);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		//stop changing stecnil buffer
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glDisable(GL_CULL_FACE);

		//check for things inside stencil
		glStencilFunc(GL_EQUAL, 1, 1);
		//disable shadow casting light for shadowed part
		glDisable(GL_LIGHT5);

		//render shadowed part
		//render christmas tree
		tree.renderTree(baubleRotation);
		//render floor
		glPushMatrix();
			glTranslatef(-10, 0, 45);
			glRotatef(-90, 1, 0, 0);
			glBindTexture(GL_TEXTURE_2D, grTex);
			floor.renderQuadShape();
		glPopMatrix();

		//re-enable light
		glEnable(GL_LIGHT5);

		//lit part has already been rendered in scene for transparency
		glDisable(GL_STENCIL_TEST);

		//clear stencil buffer to avoid overlap
		glClear(GL_STENCIL_BUFFER_BIT);

	glPopMatrix();

}

void ShadowVolume::renderShadowVolume()
{
	//render volume as explained in lecture
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_STENCIL_TEST);
	glDepthMask(GL_FALSE);
	glStencilFunc(GL_ALWAYS, 0, 0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, shadowVolQ.data());

	glDrawArrays(GL_QUADS, 0, shadowVolQ.size() / 3);

	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	glCullFace(GL_BACK);
	glVertexPointer(3, GL_FLOAT, 0, shadowVolQ.data());

	glDrawArrays(GL_QUADS, 0, shadowVolQ.size() / 3);
}

