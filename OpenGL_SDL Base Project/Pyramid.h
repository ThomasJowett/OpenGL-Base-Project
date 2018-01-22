#ifndef _PYRAMID_H
#define _PYRAMID_H

#include <Windows.h> //Required for OpenGL on Windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> //OpenGL Utilities
#include "Commons.h"
#include "Texture2D.h"

class Pyramid
{
private:
	Vector3D * indexedVertices,* normals;
	TexCoord * texCoords;
	
	short * indices;

	int numVertices;
	int indexCount;

	bool Load(char* path, char* texturepath, int width, int height);
	void DrawTriangle(short a, short b, short c);

public:
	Pyramid(void);
	~Pyramid(void);

	void Draw(void);
	void Update(void);
};

#endif
