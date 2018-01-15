#pragma once


#include <vector>
#include "Commons.h"
#include <iostream>
#include <Windows.h>
#include <gl/GL.h>

//class Renderer;


enum Enum
{
	PERSPECTIVE, ORTHO, POSITION, AIMAT, UPDIRECTION, ASPECT,
	MNEAR, MFAR, YANGLE,
	BLACK, WHITE, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, GREY,
	WIDTH, HEIGHT, DEPTH,
	AMBIENT, DIFFUSE, SPECULAR, SPOT_DIRECTION, DROPOFFRATE,
	CUTOFFANGLE, EMISSION, SHININESS,
	TRANSLATION, ROTATION, SCALE,
	BUFFER, SINGLE, MDOUBLE,
	RADIUS,
	STYLE, POINTSIZE, LINEWIDTH, FILLED, LINE, MPOINT,
	BACKCOLOR
};

class SceneNode {
public:
	SceneNode();
	virtual ~SceneNode();
	virtual void Render();
	void AddChild(SceneNode *);
	void Traverse();

protected:
	bool mKeepMatrix;
	
	SceneNode * pLeftChild;
	SceneNode * pRightSibling;


};