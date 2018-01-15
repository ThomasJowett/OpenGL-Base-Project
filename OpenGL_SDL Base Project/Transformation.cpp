#include "Transformation.h"

Transformation::Transformation()
{
	int i;

	OpNum = 0;
	for (i = 0; i < 10; i++)
		TransformOrder[i] = -1;
}

void Transformation::SetValuev(Enum pName, float * value, int order)
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
		Transform[order][i] = value[i];
	if (pName == ROTATION)
		Transform[order][3] = value[3];
}

void Transformation::SetValue(Enum pName, float x, float y, float z, int order)
{
	float temp[] = { x, y, z };

	SetValuev(pName, temp, order);
}

void Transformation::SetValue(Enum pName, float a, float x, float y, float z, int order)
{
	float temp[] = { a, x, y, z };

	SetValuev(pName, temp, order);
}

void Transformation::Render()
{
	int i;

	for (i = OpNum - 1; i >= 0; i--)
	{
		switch (TransformOrder[i])
		{
		case TRANSLATION:
			glTranslatef(Transform[i][0], Transform[i][1], Transform[i][2]);
			break;
		case ROTATION:
			glRotatef(Transform[i][0], Transform[i][1], Transform[i][2],Transform[i][3]);
			break;
		case SCALE:
			glScalef(Transform[i][0], Transform[i][1], Transform[i][2]);
			break;
		default:
			break;
		}
	}
}
