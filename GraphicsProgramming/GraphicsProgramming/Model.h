// Model class, represents a loaded OBJ model
// handles the loading/processing of the model file. Also loads and stores its own texture
// NOT complete, for students to complete. Model data requires being sorted and the render function needs completed.
#ifndef _MODEL_H_
#define _MODEL_H_

// INCLUDES //
#include <glut.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>

using namespace std;

// MY CLASS INCLUDES //
#include <vector>
#include "Vector3.h"
#include "SOIL.h"

class Model
{

private:

	void loadTexture(char*);
	bool loadModel(char*);

	int m_vertexCount;
	GLuint texture;

	vector<float> vertex, normals, texCoords;

public:

	bool load(char* modelFilename, char* textureFilename);
	void render();
	vector<float> getVertex() { return vertex; };

};

#endif