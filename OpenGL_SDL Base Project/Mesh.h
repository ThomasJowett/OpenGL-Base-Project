#pragma once
#include "Vector.h"
#include <glew.h>
#include <vector>
#include "Commons.h"


class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	virtual ~Mesh();
	void Draw();

private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NUM_BUFFERS
	};

	GLuint mVertexArrayObject;
	GLuint mVertexArrayBuffers[NUM_BUFFERS];
	unsigned int mDrawCount;
};

