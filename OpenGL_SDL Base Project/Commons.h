#pragma once
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <vector>
#include "Vector.h"

//3DS Max Object type details.
#define MAX_VERTICES 8000
#define MAX_POLYGONS 8000

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

struct Lighting {
	float ambient[4];
	float diffuse[4];
	float specular[4];
};

struct Material {
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float specularPower;
};

struct TexCoord {
	float u;
	float v;
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D(float initialX, float initialY, float initialWidth, float initialHeight)
	{
		x = initialX;
		y = initialY;
		width  = initialWidth;
		height = initialHeight;
	}

};

//The polygon (triangle), 3 numbers that aim 3 vertices
struct Triangle {
	int a;
	int b;
	int c;
};

//The obect type
struct MeshData
{
	char name[20];
	int vertices_qty;
	int triangles_qty;
	Vector3D vertices[MAX_VERTICES];
	Triangle triangles[MAX_POLYGONS];
	TexCoord texCoords[MAX_VERTICES];
	Triangle texCoordIndices[MAX_POLYGONS];
	Vector3D normals[MAX_VERTICES];
	Triangle normalsIndices[MAX_POLYGONS];
};