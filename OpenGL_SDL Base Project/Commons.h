#pragma once
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <vector>
#include "Vector.h"

//3DS Max Object type details.
#define MAX_VERTICES 80000
#define MAX_POLYGONS 80000

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
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
	float shininess;
};

struct TexCoord {
	float u;
	float v;
};

/*
struct Vertex3D
{
	float x;
	float y;
	float z;

	Vertex3D(double initialX, double initialY, double initialZ)
	{
		x = initialX;
		y = initialY;
		z = initialZ;
	}

	Vertex3D()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

};
*/
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

typedef struct
{
	char name[20];
	int vertices_qty;
	int triangles_qty;
	std::vector<Vector3D> Vertices;
	Vector3D vertex[MAX_VERTICES];
	Triangle triangle[MAX_POLYGONS];
	TexCoord texCoord[MAX_VERTICES];
	Triangle texCoordIndices[MAX_POLYGONS];
	Vector3D normals[MAX_VERTICES];
	Triangle normalsIndices[MAX_POLYGONS];
	int id_texture;
}	obj_type, *obj_type_ptr;