#pragma once


#include <vector>
#include "Commons.h"
#include <iostream>
#include <Windows.h>
#include <gl/GL.h>
#include "Transform.h"

enum Enum
{
	TRANSLATION, ROTATION, SCALE
};

class SceneNode {
public:
	SceneNode();
	virtual ~SceneNode();
	void AddChild(SceneNode *);
	virtual void Render() {}
	void Traverse();

protected:
	bool mKeepMatrix;
	
	SceneNode * pLeftChild;
	SceneNode * pRightSibling;
};