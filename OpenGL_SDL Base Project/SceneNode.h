#pragma once

#include <vector>
#include "Commons.h"
#include <iostream>
#include <Windows.h>
#include <gl/GL.h>
#include "Transform.h"

class SceneNode {
public:
	SceneNode();
	SceneNode(Transform* transform);
	virtual ~SceneNode();
	void AddChild(SceneNode *);
	virtual void Render() { mTransform->UpdateWorldMatrix(); }
	void Traverse();

	void SetTransform(Transform * transform) { mTransform = transform; }
	Transform * GetTransform() const { return mTransform; }
	Transform GetWorldTransform() const;

protected:
	Transform* mTransform;
	bool mKeepMatrix;
	
	SceneNode * pParent;
	SceneNode * pLeftChild;
	SceneNode * pRightSibling;
	SceneNode * pLeftSibling;
};