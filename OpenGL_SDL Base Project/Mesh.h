#pragma once
#include "Vector.h"
#include <glew.h>
#include <vector>
#include "Commons.h"
#include "OBJLoader2.h"


class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	virtual ~Mesh();
	void Draw();

private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint mVertexArrayObject;
	GLuint mVertexArrayBuffers[NUM_BUFFERS];
	unsigned int mDrawCount;

	void InitMesh(const IndexedModel& model);
};

