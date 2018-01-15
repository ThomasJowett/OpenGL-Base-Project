#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Windows.h>
#include "SceneNode.h"

class Transformation : public SceneNode
{
public:
	Transformation();
	void SetValuev(Enum pName, float *, int order);
	void SetValue(Enum pName, float x, float y, float z, int order);
	void SetValue(Enum pName, float a, float x, float y, float z, int order);
	void Render();

private:
	int OpNum;
	int TransformOrder[10];
	float Transform[10][4];
};


#endif // !TRANSFORM_H


