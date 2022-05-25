#ifndef _SHAPE_H
#define _SHAPE_H

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <vector>
#include "Vector3.h"

class Shape
{

	private:
		//generation calculation variables
		float interval, intervalT, intervalD;
		float Theta = 0, Delta = 0;
		float def;
		//bool for cone normals
		bool cone = false;

		//vertex arrays
		std::vector<float> verts;
		std::vector<float> norms;
		std::vector<float> texcoords;
		//function to return positive value of float
		float posNum(float);

	public:
		//generation methods
		void generateSphere(float res);
		void generateCylinder(float res, float height);
		void generateDome(float res);
		void generateQuad(float width, float height);
		void generatePlane(float x, float y, float divide);
		void generatePlane(float x, float y, float divide, char axis, float xPos, float yPos, float zPos);
		void generateTrianglePlane(float dimension, float divide);
		void generateBox(float width, float height, float depth);
		void generateCone(float height, float radius, float res);
		void generateTorus(float radius, float tubeR, float res, float stacks);

		//render methods
		void renderTriFanShape();
		void renderQuadShape();
		void renderTriangleShape();

		std::vector<float> getVerts() { return verts; };

};
#endif 
