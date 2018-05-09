#include "Mesh.h"



Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	mDrawCount = numVertices;

	glGenVertexArrays(1, &mVertexArrayObject);
	glBindVertexArray(mVertexArrayObject);

	std::vector<Vector3D>positions;
	std::vector<Vector2D>texCoords;

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (int i = 0; i < numVertices; i++)
	{
		positions.push_back(vertices[i].mPosition);
		texCoords.push_back(vertices[i].mTexCoord);
	}

	glGenBuffers(NUM_BUFFERS, mVertexArrayBuffers);

	//Position-------------------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//TexCoord-------------------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &mVertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(mVertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, mDrawCount);
	glBindVertexArray(0);
}
