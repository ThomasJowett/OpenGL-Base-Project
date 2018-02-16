#include "Transform.h"

Transform::Transform()
{
	mPosition = Vector3D{ 0.0f, 0.0f, 0.0f };
	mRotation = Vector3D{ 0.0f, 0.0f, 0.0f };
	mScale = Vector3D{ 1.0f, 1.0f, 1.0f };

	int i;

	OpNum = 0;
	for (i = 0; i < 10; i++)
		TransformOrder[i] = -1;
}

Transform::Transform(Vector3D position, Vector3D rotation, Vector3D scale) : mPosition(position), mRotation(rotation), mScale(scale)
{
	int i;

	OpNum = 0;
	for (i = 0; i < 10; i++)
		TransformOrder[i] = -1;
}
/*
void Transform::SetValuev(Enum pName, float * value, int order)
{
	int i;
	
	if (OpNum < order + 1)
		OpNum = order + 1;

	switch (pName)
	{
	case TRANSLATION:
		TransformOrder[order] = TRANSLATION;
		break;
	case ROTATION:
		TransformOrder[order] = ROTATION;
		break;
	case SCALE:
		TransformOrder[order] = SCALE;
		break;
	default:
		break;
	}

	for (i = 0; i < 3; i++)
		transform[order][i] = value[i];
	if (pName == ROTATION)
		transform[order][3] = value[3];
}

void Transform::SetValue(Enum pName, float x, float y, float z, int order)
{
	float temp[] = { x, y, z };

	SetValuev(pName, temp, order);
}

void Transform::SetValue(Enum pName, float a, float x, float y, float z, int order)
{
	float temp[] = { a, x, y, z };

	SetValuev(pName, temp, order);
}
*/
void Transform::UpdateWorldMatrix()
{
	/*
	int i;

	for (i = OpNum - 1; i >= 0; i--)
	{
		switch (TransformOrder[i])
		{
		case TRANSLATION:
			
			//glTranslatef(transform[i][0], transform[i][1], transform[i][2]);
			break;
		case ROTATION:
			
			//glRotatef(transform[i][0], transform[i][1], transform[i][2], transform[i][3]);
			break;
		case SCALE:
			
			//glScalef(transform[i][0], transform[i][1], transform[i][2]);
			break;
		default:
			break;
		}
	}
	*/
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	glRotatef(mRotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(mRotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(mRotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(mScale.x, mScale.y, mScale.z);
}
