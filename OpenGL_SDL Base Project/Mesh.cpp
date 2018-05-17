#include "Mesh.h"

void IndexedModel::CalcNormals()
{
	for (unsigned int i = 0; i < indices.size(); i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		Vector3D v1 = positions[i1] - positions[i0];
		Vector3D v2 = positions[i2] - positions[i0];

		Vector3D normal = Vector3D::Cross(v1, v2).GetNormalized();

		normals[i0] += normal;
		normals[i1] += normal;
		normals[i2] += normal;
	}

	for (unsigned int i = 0; i < positions.size(); i++)
		normals[i].Normalize();
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	mDrawCount = numIndices;

	glGenVertexArrays(1, &mVertexArrayObject);
	glBindVertexArray(mVertexArrayObject);

	std::vector<Vector3D>positions;
	std::vector<Vector2D>texCoords;

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(vertices[i].mPosition);
		model.texCoords.push_back(vertices[i].mTexCoord);
		model.normals.push_back(vertices[i].mNormal);
	}

	for (int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}

	InitMesh(model);
}

Mesh::Mesh(IndexedModel model)
{
	InitMesh(model);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &mVertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(mVertexArrayObject);
	//glDrawArrays(GL_TRIANGLES, 0, mDrawCount);
	glDrawElementsBaseVertex(GL_TRIANGLES, mDrawCount, GL_UNSIGNED_INT, 0, 0);
	glBindVertexArray(0);
}

void Mesh::InitMesh(const IndexedModel & model)
{
	mDrawCount = model.indices.size();

	glGenVertexArrays(1, &mVertexArrayObject);
	glBindVertexArray(mVertexArrayObject);

	glGenBuffers(NUM_BUFFERS, mVertexArrayBuffers);

	//Position-------------------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//TexCoord-------------------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Normal-------------------------------------------------------------------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Indices--------------------------------------------------------------------------------------------
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}
