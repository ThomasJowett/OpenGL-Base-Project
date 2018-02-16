#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Windows.h>
//#include "SceneNode.h"
#include "Vector.h"
#include <gl/GL.h>

class Transform
{
public:
	Transform();
	Transform(Vector3D position, Vector3D rotation, Vector3D scale);
	//void SetValuev(Enum pName, float *, int order);
	//void SetValue(Enum pName, float x, float y, float z, int order);
	//void SetValue(Enum pName, float a, float x, float y, float z, int order);

	void SetPosition(float x, float y, float z) { mPosition = Vector3D{ x,y,z }; }
	void SetPosition(Vector3D position) { mPosition = position; }
	Vector3D GetPosition() const { return mPosition; }

	void SetRotation(float pitch, float roll, float yaw) { mRotation = Vector3D{ pitch , roll, yaw }; }
	void SetRotation(Vector3D rotation) { mRotation = rotation; }
	Vector3D GetRotation() const { return mRotation; }

	void SetScale(float x, float y, float z) { mScale = Vector3D{ x,y,z }; }
	void SetScale(Vector3D scale) { mScale = scale; }
	Vector3D GetScale() const { return mScale; }

	void UpdateWorldMatrix();

private:
	Vector3D mPosition;
	Vector3D mRotation;
	Vector3D mScale;
	int OpNum;
	int TransformOrder[10];
	float transform[10][4];
};


#endif // !TRANSFORM_H


