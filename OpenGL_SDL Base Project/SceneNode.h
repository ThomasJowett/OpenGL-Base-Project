#pragma once

//#include <vector>
//#include "Commons.h"
//#include <iostream>
//#include <Windows.h>
//#include "Transform.h"
#include "Shader.h"

//class Shader;

class SceneNode {
public:
	SceneNode();
	SceneNode(Transform* transform);
	virtual ~SceneNode();
	void AddChild(SceneNode *);
	void RemoveSelf();
	void RemoveSelfAndChildren();
	virtual void Render(Shader* shader);
	void Traverse(Shader* shader);

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