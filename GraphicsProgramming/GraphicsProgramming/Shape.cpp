#include "Shape.h"

float Shape::posNum(float n) {
	//function to make sure you're handling the value, not the direction
	if (n > 0) {
		return n;
	}
	else {
		return n * -1;
	}
}

void Shape::generateSphere(float res) {
	//intervals to increase angle by, depending on resolution
	intervalT = (2 * 3.1415) / res;
	intervalD = 3.1415 / res;
	//loop longitude
	for (float lon = 0; lon <  res; lon++) {
		//loop latitude
		for (float lat = 0; lat <  res; lat++) {
			//vertex 1
			verts.push_back(cosf(Theta) * sinf(Delta));
			verts.push_back(cosf(Delta));
			verts.push_back(sinf(Theta) * sinf(Delta));
			norms.push_back(cosf(Theta) * sinf(Delta));
			norms.push_back(cosf(Delta));
			norms.push_back(sinf(Theta) * sinf(Delta));
			texcoords.push_back(lat * (1 / res));
			texcoords.push_back(lon * (1 / res));

			//vertex 2
			verts.push_back(cosf(Theta) * sinf(Delta + intervalD));
			verts.push_back(cosf(Delta + intervalD));
			verts.push_back(sinf(Theta) * sinf(Delta + intervalD));
			norms.push_back(cosf(Theta) * sinf(Delta + intervalD));
			norms.push_back(cosf(Delta + intervalD));
			norms.push_back(sinf(Theta) * sinf(Delta + intervalD));
			texcoords.push_back(lat * (1 / res));
			texcoords.push_back((lon+1) * (1 / res));

			//vertex 3
			verts.push_back(cosf(Theta + intervalT) * sinf(Delta + intervalD));
			verts.push_back(cosf(Delta + intervalD));
			verts.push_back(sinf(Theta + intervalT) * sinf(Delta + intervalD));
			norms.push_back(cosf(Theta + intervalT) * sinf(Delta + intervalD));
			norms.push_back(cosf(Delta + intervalD));
			norms.push_back(sinf(Theta + intervalT) * sinf(Delta + intervalD));
			texcoords.push_back((lat+1) * (1 / res));
			texcoords.push_back((lon+1) * (1 / res));

			//vertex 4
			verts.push_back(cosf(Theta + intervalT) * sinf(Delta));
			verts.push_back(cosf(Delta));
			verts.push_back(sinf(Theta + intervalT) * sinf(Delta));
			norms.push_back(cosf(Theta + intervalT) * sinf(Delta));
			norms.push_back(cosf(Delta));
			norms.push_back(sinf(Theta + intervalT) * sinf(Delta));
			texcoords.push_back((lat+1) * (1 / res));
			texcoords.push_back(lon * (1 / res));


			Theta += intervalT;
		}
		Delta += intervalD;
	}
}

void Shape::generateCylinder(float res, float height) {
	//interval depending on resolution
	interval = (2 * 3.1415) / res;

	//loop stacks/height
	for (float i = 0; i < height; i++) {
		//loop ring
		for (float j = 0; j < res; j++) {
			//x
			verts.push_back(cosf(Theta));
			norms.push_back(cosf(Theta));
			texcoords.push_back(j * (1 / res));
			//y
			verts.push_back(i + 1);
			norms.push_back(i + 1);
			texcoords.push_back(1 - ((i + 1) * (1 / height)));
			//z
			verts.push_back(sinf(Theta));
			norms.push_back(sinf(Theta));
			//x1
			verts.push_back(cosf(Theta));
			norms.push_back(cosf(Theta));
			texcoords.push_back(j * (1 / res));
			//y1
			verts.push_back(i);
			norms.push_back(i);
			texcoords.push_back(1 - (i * (1 / height)));
			//z1
			verts.push_back(sinf(Theta));
			norms.push_back(sinf(Theta));

			Theta += interval;

			//x2
			verts.push_back(cosf(Theta));
			norms.push_back(cosf(Theta));
			texcoords.push_back((j + 1) * (1 / res));
			//y2
			verts.push_back(i);
			norms.push_back(i);
			texcoords.push_back(1 - (i * (1 / height)));
			//z2
			verts.push_back(sinf(Theta));
			norms.push_back(sinf(Theta));
			//x3
			verts.push_back(cosf(Theta));
			norms.push_back(cosf(Theta));
			texcoords.push_back((j + 1) * (1 / res));
			//y3
			verts.push_back(i + 1);
			norms.push_back(i + 1);
			texcoords.push_back(1 - ((i + 1) * (1 / height)));
			//z3
			verts.push_back(sinf(Theta));
			norms.push_back(sinf(Theta));


		}
	}
}

void Shape::generateDome(float res) {
	//generate half a sphere
	intervalT = (2 * 3.1415) / res;
	intervalD = 3.1415 / res / 2;
	for (float lon = 0; lon < res; lon++) {
		for (float lat = 0; lat < res; lat++) {
			//vertex 1
			verts.push_back(cosf(Theta) * sinf(Delta));
			verts.push_back(cosf(Delta));
			verts.push_back(sinf(Theta) * sinf(Delta));
			norms.push_back(cosf(Theta) * sinf(Delta));
			norms.push_back(cosf(Delta));
			norms.push_back(sinf(Theta) * sinf(Delta));
			texcoords.push_back(lat * (1 / res));
			texcoords.push_back(lon * (1 / res));

			//vertex 2
			verts.push_back(cosf(Theta) * sinf(Delta + intervalD));
			verts.push_back(cosf(Delta + intervalD));
			verts.push_back(sinf(Theta) * sinf(Delta + intervalD));
			norms.push_back(cosf(Theta) * sinf(Delta + intervalD));
			norms.push_back(cosf(Delta + intervalD));
			norms.push_back(sinf(Theta) * sinf(Delta + intervalD));
			texcoords.push_back(lat * (1 / res));
			texcoords.push_back((lon + 1) * (1 / res));

			//vertex 3
			verts.push_back(cosf(Theta + intervalT) * sinf(Delta + intervalD));
			verts.push_back(cosf(Delta + intervalD));
			verts.push_back(sinf(Theta + intervalT) * sinf(Delta + intervalD));
			norms.push_back(cosf(Theta + intervalT) * sinf(Delta + intervalD));
			norms.push_back(cosf(Delta + intervalD));
			norms.push_back(sinf(Theta + intervalT) * sinf(Delta + intervalD));
			texcoords.push_back((lat + 1) * (1 / res));
			texcoords.push_back((lon + 1) * (1 / res));

			//vertex 4
			verts.push_back(cosf(Theta + intervalT) * sinf(Delta));
			verts.push_back(cosf(Delta));
			verts.push_back(sinf(Theta + intervalT) * sinf(Delta));
			norms.push_back(cosf(Theta + intervalT) * sinf(Delta));
			norms.push_back(cosf(Delta));
			norms.push_back(sinf(Theta + intervalT) * sinf(Delta));
			texcoords.push_back((lat + 1) * (1 / res));
			texcoords.push_back(lon * (1 / res));


			Theta += intervalT;
		}
		Delta += intervalD;
	}

}

void Shape::generateQuad(float width, float height) {
	//generate simple quad, width by height
	//vertex1
	verts.push_back(0);
	verts.push_back(0);
	verts.push_back(0);
	texcoords.push_back(0);
	texcoords.push_back(1);
	//vertex2
	verts.push_back(width);
	verts.push_back(0);
	verts.push_back(0);
	texcoords.push_back(1);
	texcoords.push_back(1);
	//vertex3
	verts.push_back(width);
	verts.push_back(height);
	verts.push_back(0);
	texcoords.push_back(1);
	texcoords.push_back(0);
	//vertex4
	verts.push_back(0);
	verts.push_back(height);
	verts.push_back(0);
	texcoords.push_back(0);
	texcoords.push_back(0);
	//normals are all the same
	for (int i = 0; i < 4; i++) {
		norms.push_back(0);
		norms.push_back(0);
		norms.push_back(1);
	}

}

void Shape::generatePlane(float x, float y, float divide) {
	//generate x-y plane with given dimensions
	//divide marks how many quads in 1 unit
	for (float i = 0; i < y; i++) {
		for (float j = 0; j < x; j++) {
			//vertex1
			verts.push_back(j / divide);
			verts.push_back(i / divide);
			verts.push_back(0);
			texcoords.push_back(j / x);
			texcoords.push_back(-1*( i / y));
			//vertex2
			verts.push_back(j / divide);
			verts.push_back((i + 1) / divide);
			verts.push_back(0);
			texcoords.push_back(j / x);
			texcoords.push_back(-1*((i+1) / y));
			//vertex3
			verts.push_back((j + 1) / divide);
			verts.push_back((i + 1) / divide);
			verts.push_back(0);
			texcoords.push_back((j + 1) / x);
			texcoords.push_back(-1*((i + 1) / y));
			//vertex4
			verts.push_back((j + 1) / divide);
			verts.push_back(i / divide);
			verts.push_back(0);
			texcoords.push_back((j + 1) / x);
			texcoords.push_back(-1*(i / y));

			for (int k = 0; k < 4; k++) {
				//normals all the same
				norms.push_back(0);
				norms.push_back(0);
				norms.push_back(1);
			}
		}
	}
}

void Shape::generatePlane(float x, float y, float divide, char axis, float xPos, float yPos, float zPos) {
	float xP = posNum(x);
	//generate plane, on either basic plane, in any position
	//xy-plane
	if (axis == 'z') {
		for (float i = yPos; i < y + yPos; i++) {
			for (float j = xPos; j < xP + xPos; j++) {
				//vertex1
				verts.push_back(j / divide);
				verts.push_back(i / divide);
				verts.push_back(zPos);
				texcoords.push_back(j / posNum(x));
				texcoords.push_back(-1*(i / posNum(y)));
				//vertex2
				verts.push_back(j / divide);
				verts.push_back((i + 1) / divide);
				verts.push_back(zPos);
				texcoords.push_back(j / posNum(x));
				texcoords.push_back(-1*((i + 1) / posNum(y)));
				//vertex3
				verts.push_back((j + 1) / divide);
				verts.push_back((i + 1) / divide);
				verts.push_back(zPos);
				texcoords.push_back((j + 1) / posNum(x));
				texcoords.push_back(-1*((i + 1) / posNum(y)));
				//vertex4
				verts.push_back((j + 1) / divide);
				verts.push_back(i / divide);
				verts.push_back(zPos);
				texcoords.push_back((j + 1) / posNum(x));
				texcoords.push_back(-1*(i / posNum(y)));

				for (int k = 0; k < 4; k++) {
					//normals all the same
					if (x < 0) {
						norms.push_back(0);
						norms.push_back(0);
						norms.push_back(-1);

					}
					else {
						norms.push_back(0);
						norms.push_back(0);
						norms.push_back(1);
					}
				}
			}
		}
	}
	//xz-plane
	if (axis == 'y') {
		for (float i = zPos; i < y + zPos; i++) {
			for (float j = xPos; j < xP + xPos; j++) {
				//vertex1
				verts.push_back(j / divide);
				verts.push_back(yPos);
				verts.push_back(i / divide);
				texcoords.push_back(j / posNum(x));
				texcoords.push_back(-1*(i / posNum(y)));
				//vertex2
				verts.push_back(j / divide);
				verts.push_back(yPos);
				verts.push_back((i + 1) / divide);
				texcoords.push_back(j / posNum(x));
				texcoords.push_back(-1*((i + 1) / posNum(y)));
				//vertex3
				verts.push_back((j + 1) / divide);
				verts.push_back(yPos);
				verts.push_back((i + 1) / divide);
				texcoords.push_back((j + 1) / posNum(x));
				texcoords.push_back(-1*((i + 1) / posNum(y)));
				//vertex4
				verts.push_back((j + 1) / divide);
				verts.push_back(yPos);
				verts.push_back(i / divide);
				texcoords.push_back((j + 1) / posNum(x));
				texcoords.push_back(-1*(i / posNum(y)));

				for (int k = 0; k < 4; k++) {
					//normals all the same
					if (x < 0) {
						norms.push_back(0);
						norms.push_back(1);
						norms.push_back(0);
					}
					else {
						norms.push_back(0);
						norms.push_back(-1);
						norms.push_back(0);
					}
				}
			}
		}
	}
	//yz-plane
	if (axis == 'x') {
		for (float i = zPos; i < y + zPos; i++) {
			for (float j = yPos; j < xP + yPos; j++) {
				//vertex1
				verts.push_back(xPos);
				verts.push_back(j / divide);
				verts.push_back(i / divide);
				texcoords.push_back(j / posNum(x));
				texcoords.push_back(-1*(i / posNum(y)));
				//vertex2
				verts.push_back(xPos);
				verts.push_back(j / divide);
				verts.push_back((i + 1) / divide);
				texcoords.push_back(j / posNum(x));
				texcoords.push_back(-1*((i + 1) / posNum(y)));
				//vertex3
				verts.push_back(xPos);
				verts.push_back((j + 1) / divide);
				verts.push_back((i + 1) / divide);
				texcoords.push_back((j + 1) / posNum(x));
				texcoords.push_back(-1*((i + 1) / posNum(y)));
				//vertex4
				verts.push_back(xPos);
				verts.push_back((j + 1) / divide);
				verts.push_back(i / divide);
				texcoords.push_back((j + 1) / posNum(x));
				texcoords.push_back(-1*(i / posNum(y)));

				for (int k = 0; k < 4; k++) {
					//normals all the same
					if (x < 0) {
						norms.push_back(-1);
						norms.push_back(0);
						norms.push_back(0);
					}
					else {
						norms.push_back(1);
						norms.push_back(0);
						norms.push_back(0);
					}
				}
			}
		}
	}
}

void Shape::generateTrianglePlane(float dimension, float divide) {
	//render triangle shaped plane of triangles
	float y = dimension;
	float x = dimension;
	for (float i = 0; i < y; i++) {
		for (float j = 0; j < x; j++) {
			//vertex1
			verts.push_back(j / divide);
			verts.push_back(i / divide);
			verts.push_back(0);
			texcoords.push_back(j / x);
			texcoords.push_back(i / y);
			//vertex2
			verts.push_back(j / divide);
			verts.push_back((i + 1) / divide);
			verts.push_back(0);
			texcoords.push_back(j / x);
			texcoords.push_back((i + 1) / y);
			//vertex3
			verts.push_back((j + 1) / divide);
			verts.push_back(i / divide);
			verts.push_back(0);
			texcoords.push_back((j + 1) / x);
			texcoords.push_back(i / y);

			if (j != x - 1) {
				//no quad-filling triangle on the last one
				//vertex1
				verts.push_back((j + 1) / divide);
				verts.push_back(i / divide);
				verts.push_back(0);
				texcoords.push_back((j + 1) / x);
				texcoords.push_back(i / y);
				//vertex2
				verts.push_back(j / divide);
				verts.push_back((i + 1) / divide);
				verts.push_back(0);
				texcoords.push_back(j / x);
				texcoords.push_back((i + 1) / y);
				//vertex3
				verts.push_back((j + 1) / divide);
				verts.push_back((i + 1) / divide);
				verts.push_back(0);
				texcoords.push_back((j + 1) / x);
				texcoords.push_back((i + 1) / y);

				for (int k = 0; k < 6; k++) {
					//normals all the same
					norms.push_back(0);
					norms.push_back(0);
					norms.push_back(1);
				}
			}
			else {
				for (int k = 0; k < 3; k++) {
					//normals all the same
					norms.push_back(0);
					norms.push_back(0);
					norms.push_back(1);

				}
			}
		}
		//decrease x for next row up
		x -= 1;
	}

}

void Shape::generateBox(float width, float height, float depth) {
	//generate 6 planes, arranged in a cube
	generatePlane(width * 10, height * 10, 10, 'z', 0, 0, depth);
	generatePlane(-width * 10, height * 10, 10, 'z', 0, 0, 0);
	generatePlane(height * 10, depth * 10, 10, 'x', width, 0, 0);
	generatePlane(-height * 10, depth * 10, 10, 'x', 0, 0, 0);
	generatePlane(width * 10, depth * 10, 10, 'y', 0, 0, 0);
	generatePlane(-width * 10, depth * 10, 10, 'y', 0, height, 0);
}

void Shape::generateCone(float height, float radius, float res) {

	//save resolution for rendering
	def = res;
	interval = (2 * 3.1415) / res;
	//centre of circle
	verts.push_back(0);
	verts.push_back(height);
	verts.push_back(0);

	norms.push_back(0);
	//if it's not the disc at the bottom of a cone, normal normals
	if (!cone) {
		norms.push_back(1);
		norms.push_back(0);
	}
	else {
		norms.push_back(-1);
		norms.push_back(0);
	}

	texcoords.push_back(0.5);
	texcoords.push_back(0.5);
	//loop through vertex array coordinates
	for (int i = 3; i <= 3 * (res + 1); i += 3) {
		verts.push_back(cosf(Theta)*radius);
		verts.push_back(0);
		verts.push_back(sinf(Theta)*radius);

		Theta += interval;
	}
	//reset Theta
	Theta = 0;
	//texture loop
	for (int i = 2; i <= 2 * (res + 1); i += 2) {
		texcoords.push_back((cosf(Theta) / 2) + 0.5);
		texcoords.push_back((sinf(Theta) / 2) + 0.5);
		Theta += interval;
	}

	Vector3 vec1, vec2, norm;

	//normal loop
	for (int i = 3; i < verts.size()-3; i += 3) {
		//calculate position vectors of vertices
		vec1.x = verts[i];
		vec1.y = verts[i + 1];
		vec1.z = verts[i + 2];
		vec2.x = verts[i + 3];
		vec2.y = verts[i + 4];
		vec2.z = verts[i + 5];

		//take angle between them
		norm = vec2.cross(vec1);
		norms.push_back(norm.x);
		//if simple disc or cone, cone is false, therefore the calculated normal will be used
		//if generatecone has been called the second time, for the bottom of the cone,
		//cone is true and the normal will point down
		if (!cone) {
			//if it's not the disc at the bottom of a cone, normal normals
			norms.push_back(norm.y);
		}
		else {
			//if disc to close off cone, normals pointing down
			norms.push_back(-1);
		}
		norms.push_back(norm.z);

	}
	if (height != 0) {
		//if called a second time to close a cone, make sure the normals will be right
		cone = true;
		generateCone(0, radius, res);
	}
}

void Shape::generateTorus(float radius, float tubeR, float rings, float res) {
	
	//indicate how often the texture should repeat over the torus
	int texRepeat = 5;
	//ring/tube angle
	Theta = 0;
	//big angle
	Delta = 0;
	intervalD = (2 * 3.1415) / rings;
	intervalT = (2 * 3.1415) / res;
	
	for (float i = 0; i < rings; i++) {
		for (float j = 0; j < res; j++) {
			//vertex 1
			//bottom left
			verts.push_back((radius + (tubeR * cosf(Theta))) * cosf(Delta));
			verts.push_back((radius + (tubeR * cosf(Theta))) * sinf(Delta));
			verts.push_back(tubeR * sinf(Theta));
			norms.push_back((((radius + (tubeR * cosf(Theta))) * cosf(Delta)) - (radius * cosf(Delta))) / tubeR);
			norms.push_back((((radius +	(tubeR * cosf(Theta))) * sinf(Delta)) - (radius * sinf(Delta))) / tubeR);
			norms.push_back(sinf(Theta));
			texcoords.push_back(texRepeat * i / rings);
			texcoords.push_back(texRepeat * j / res);

			//vertex 2
			//bottom right
			verts.push_back((radius + (tubeR * cosf(Theta))) * cosf(Delta + intervalD));
			verts.push_back((radius + (tubeR * cosf(Theta))) * sinf(Delta + intervalD));
			verts.push_back(tubeR * sinf(Theta));
			norms.push_back((((radius + (tubeR * cosf(Theta))) * cosf(Delta + intervalD)) - (radius * cosf(Delta + intervalD))) / tubeR);
			norms.push_back((((radius + (tubeR * cosf(Theta))) * sinf(Delta + intervalD)) - (radius * sinf(Delta + intervalD))) / tubeR);
			norms.push_back(sinf(Theta));
			texcoords.push_back(texRepeat * (i + 1) / rings);
			texcoords.push_back(texRepeat * j / res);

			//vertex 3
			//top right
			verts.push_back((radius + (tubeR * cosf(Theta + intervalT))) * cosf(Delta + intervalD));
			verts.push_back((radius + (tubeR * cosf(Theta + intervalT))) * sinf(Delta + intervalD));
			verts.push_back(tubeR * sinf(Theta + intervalT));
			norms.push_back((((radius + (tubeR * cosf(Theta + intervalT))) * cosf(Delta + intervalD)) - (radius * cosf(Delta + intervalD))) / tubeR);
			norms.push_back((((radius + (tubeR * cosf(Theta + intervalT))) * sinf(Delta + intervalD)) - (radius * sinf(Delta + intervalD))) / tubeR);
			norms.push_back(sinf(Theta + intervalT));
			texcoords.push_back(texRepeat * (i + 1) / rings);
			texcoords.push_back(texRepeat * (j + 1) / res);

			//vertex 4
			//top left
			verts.push_back((radius + (tubeR * cosf(Theta + intervalT))) * cosf(Delta));
			verts.push_back((radius + (tubeR * cosf(Theta + intervalT))) * sinf(Delta));
			verts.push_back(tubeR * sinf(Theta + intervalT));
			norms.push_back((((radius + (tubeR * cosf(Theta + intervalT))) * cosf(Delta)) - (radius * cosf(Delta))) / tubeR);
			norms.push_back((((radius + (tubeR * cosf(Theta + intervalT))) * sinf(Delta)) - (radius * sinf(Delta))) / tubeR);
			norms.push_back(sinf(Theta + intervalT));
			texcoords.push_back(texRepeat * i / rings);
			texcoords.push_back(texRepeat * (j + 1) / res);

		Theta += intervalT;
		}
		Theta = 0;
		Delta += intervalD;
	}

}

void Shape::renderTriFanShape() {
	//render shape made of triangle fan
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts.data());
	glNormalPointer(GL_FLOAT, 0, norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords.data());

	glDrawArrays(GL_TRIANGLE_FAN, 0, def+2);

	if (cone) {
		//render second triangle fan shape, for the second half of the same arrays
		glDrawArrays(GL_TRIANGLE_FAN, def + 2, def + 2);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

void Shape::renderQuadShape() {
	//render shape made of quads
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glVertexPointer(3, GL_FLOAT, 0, verts.data());
	glNormalPointer(GL_FLOAT, 0, norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords.data());

	glDrawArrays(GL_QUADS, 0, verts.size()/3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

void Shape::renderTriangleShape() {
	//render shape made of triangles
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts.data());
	glNormalPointer(GL_FLOAT, 0, norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords.data());

	glDrawArrays(GL_TRIANGLES, 0, verts.size() / 3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}