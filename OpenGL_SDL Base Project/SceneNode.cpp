#include "SceneNode.h"

SceneNode::SceneNode()
{
	mKeepMatrix = false;
	pLeftChild = NULL;
	pRightSibling = NULL;
}

SceneNode::~SceneNode()
{
	if (pLeftChild)
		delete pLeftChild;
	pLeftChild = NULL;
	if (pRightSibling)
		delete pRightSibling;
	pRightSibling = NULL;
}

void SceneNode::Render()
{
}

void SceneNode::AddChild(SceneNode *node)
{
	if (pLeftChild == NULL)
		pLeftChild = node;
	else
	{
		node->pRightSibling = pLeftChild;
		pLeftChild = node;
	}
}

void SceneNode::Traverse()
{
	if (!mKeepMatrix)
		glPushMatrix();

	Render();
	if (pLeftChild != NULL)
		pLeftChild->Traverse();
	if (!mKeepMatrix)
		glPopMatrix();
	if (pRightSibling != NULL)
		pRightSibling->Traverse();
}