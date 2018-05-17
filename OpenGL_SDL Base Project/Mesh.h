#pragma once
#include "Vector.h"
#include <vector>
#include "Commons.h"

struct IndexedModel
{
public:
	std::vector<Vector3D> positions;
	std::vector<Vector2D> texCoords;
	std::vector<Vector3D> normals;
	std::vector<unsigned int> indices;

	void CalcNormals();
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(IndexedModel model);
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

