#pragma once


#include <vector>
#include "Commons.h"
#include <iostream>
#include <Windows.h>
#include <gl/GL.h>

enum Enum
{
	TRANSLATION, ROTATION, SCALE
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