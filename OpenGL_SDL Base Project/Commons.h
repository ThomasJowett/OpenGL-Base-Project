#pragma once
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <vector>

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

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initialX, float initialY)
	{
		x = initialX;
		y = initialY;
	}
};

struct Vector3D
{
	float x;
	float y;
	float z;

	Vector3D()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3D(double initialX, double initialY, double initialZ)
	{
		x = initialX;
		y = initialY;
		z = initialZ;
	}

	double GetMagnitude()
	{
		return sqrtf((x*x) + (y*y) + (z*z));
	}

	Vector3D GetNormalised()
	{
		double magnitude = GetMagnitude();
		return Vector3D{ x / magnitude, y / magnitude, z / magnitude };
	}

	Vector3D Cross(Vector3D v1, Vector3D v2)
	{
		Vector3D cross;
		cross.x = (v1.y*v2.z) - (v1.z*v2.y);
		cross.y = -((v1.x*v2.z) - (v1.z*v2.x));
		cross.z = (v1.x*v2.y) - (v1.y*v2.x);
		return cross;
	}

	Vector3D MakeVector(Vertex3D source, Vertex3D destination)
	{
		Vector3D OutPutVector;
		OutPutVector.x = source.x - destination.x;
		OutPutVector.y = source.y - destination.y;
		OutPutVector.z = source.z - destination.z;
		return OutPutVector;
	}

	Vector3D operator*(float scaler)
	{
		return Vector3D(x * scaler, y * scaler, z * scaler);
	}

	Vector3D operator+ (const Vector3D& other)
	{
		return Vector3D(x + other.x, y + other.y, z + other.z);
	}

	Vector3D operator+= (const Vector3D& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3D operator-= (const Vector3D& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
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
	std::vector<Vertex3D> Vertices;
	Vertex3D vertex[MAX_VERTICES];
	Triangle triangle[MAX_POLYGONS];
	TexCoord texCoord[MAX_VERTICES];
	Triangle texCoordIndices[MAX_POLYGONS];
	Vector3D normals[MAX_VERTICES];
	Triangle normalsIndices[MAX_POLYGONS];
	int id_texture;
}	obj_type, *obj_type_ptr;