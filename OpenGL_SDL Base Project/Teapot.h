#pragma once
#include "Commons.h"
class Sphere;
class Teapot {
public:
	Teapot();
	~Teapot() { }
	void Update();
	void Render();
	Sphere * GetBoundingSphere();
private:
	Vector3D position;
	float scale;
	Vector3D velocity;
	Sphere * boundingSphere;
};