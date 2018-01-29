#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Windows.h>
#include "SceneNode.h"
#include "Vector.h"

class Transformation : public SceneNode
{
public:
	Transformation();
	void SetValuev(Enum pName, float *, int order);
	void SetValue(Enum pName, float x, float y, float z, int order);
	void SetValue(Enum pName, float a, float x, float y, float z, int order);
	void Render();

private:
	Vector3D mPosition;
	Vector3D mRotation;
	Vector3D mScale;

	int OpNum;
	int TransformOrder[10];
	float Transform[10][4];
};


#endif // !TRANSFORM_H


