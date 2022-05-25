#include "Tree.h"

void Tree::generateTree() {
	//generate single shapes
	cone.generateCone(5, 2, 20);
	sphere.generateSphere(40);
	stem.generateCylinder(20, 2);
	imposter.generateQuad(4.4, 4.4);

	//load textures
	feather = SOIL_load_OGL_texture(
		"gfx/feather.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	flowers = SOIL_load_OGL_texture(
		"gfx/china1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	baubles = SOIL_load_OGL_texture(
		"gfx/China2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	bark = SOIL_load_OGL_texture(
		"models/tree/maple_bark.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	imposterTex = SOIL_load_OGL_texture(
		"gfx/grassImposter.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

}

void Tree::renderTree(float rotation) {
	
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		//default colour
		glColor3f(1, 1, 1);
		//translate to position
		glTranslatef(12, 0, 3);
		glPushMatrix();
		//render tree shadow (imposter)
			glBindTexture(GL_TEXTURE_2D, imposterTex);
			//translate slightly up to avoid z-fighting
			//translate by half its width and depth to centre under tree
			glTranslatef(-2.2, 0.01, 2.2);
			//rotate to have it be parallel to the floor
			glRotatef(-90, 1, 0, 0);
			imposter.renderQuadShape();
		glPopMatrix();
		glPushMatrix();
			//render tree stem (cylinder)
			glScalef(0.7, 1, 0.7);
			glBindTexture(GL_TEXTURE_2D, bark);
			stem.renderQuadShape();
		glPopMatrix();
		//render treetop/leaves (cone)
		glBindTexture(GL_TEXTURE_2D, feather);
		glColor3f(0.5, 0.8, 0);
		glTranslatef(0, 2, 0);
		cone.renderTriFanShape();
		//matrix stack for bauble animation
		glPushMatrix();
			glTranslatef(0, 5, 0);
			glPushMatrix();
				//red light on top
				glScalef(0.5, 0.5, 0.5);
				glColor3f(0.8, 0, 0);
				//set texture and material values
				glBindTexture(GL_TEXTURE_2D, flowers);
				glMaterialfv(GL_FRONT, GL_EMISSION, emission_red);
				sphere.renderQuadShape();
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
			glPopMatrix();
			//BAUBLES
			//different materials, hierarchical animation
			glDisable(GL_COLOR_MATERIAL);
			glBindTexture(GL_TEXTURE_2D, baubles);
			glPushMatrix();
				//top bauble, blue
				glRotatef(rotation, 0, 1, 0);
				glTranslatef(0.4, -1, 0);
				//material settings
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_blue);
				glMaterialfv(GL_FRONT, GL_SPECULAR, highSpec);
				glMaterialfv(GL_FRONT, GL_SHININESS, high_shiny);
				glPushMatrix();
					glScalef(0.3, 0.3, 0.3);
					sphere.renderQuadShape();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				//middle bauble, dark orange
				glRotatef(rotation, 0, 1, 0);
				glTranslatef(0, -3, 1.2);
				//material settings
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_orange);
				glMaterialfv(GL_FRONT, GL_SPECULAR, lowSpec);
				glMaterialfv(GL_FRONT, GL_SHININESS, low_shiny);
				glPushMatrix();
					glScalef(0.3, 0.3, 0.3);
					sphere.renderQuadShape();
				glPopMatrix();
				glTranslatef(0.3, 0, -2.4);
				glPushMatrix();
					glScalef(0.3, 0.3, 0.3);
					sphere.renderQuadShape();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				//bottom baubles, purple
				glRotatef(rotation, 0, 1, 0);
				glTranslatef(-1.9, -4.9, 0);
				//material settings
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_purple);
				glMaterialfv(GL_FRONT, GL_SPECULAR, highSpec);
				glMaterialfv(GL_FRONT, GL_SHININESS, medium_shiny);
				glPushMatrix();
					glScalef(0.2, 0.2, 0.2);
					sphere.renderQuadShape();
				glPopMatrix();

				glRotatef(rotation*2, 0, 1, 0);

				glPushMatrix();
					glTranslatef(0.2, -0.3, 0);
					glScalef(0.1, 0.1, 0.1);
					sphere.renderQuadShape();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, -0.4, 0.2);
					glScalef(0.1, 0.1, 0.1);
					sphere.renderQuadShape();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	//reset all material values
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shiny);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1, 1, 1);
}