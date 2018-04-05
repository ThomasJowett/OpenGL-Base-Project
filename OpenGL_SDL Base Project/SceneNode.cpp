#include "SceneNode.h"

SceneNode::SceneNode()
{
	mKeepMatrix = false;
	pParent = NULL;
	pLeftChild = NULL;
	pRightSibling = NULL;
	pLeftSibling = NULL;
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

void SceneNode::AddChild(SceneNode *node)
{
	if (node->pParent != NULL)
	{
		if (node->pParent->pLeftChild != node)
		{
			node->pParent->pLeftChild = node->pRightSibling;
		}

		if (node->pLeftSibling != NULL)
		{
			node->pLeftSibling->pRightSibling = node->pRightSibling;

			if (node->pRightSibling != NULL)
			{
				node->pRightSibling->pLeftSibling = node->pLeftSibling;
			}
		}

		node->pParent = this;
		node->pLeftSibling = NULL;
		node->pRightSibling = NULL;

		if (pLeftChild == NULL)
		{
			pLeftChild = node;
		}
		else
		{
			node->pRightSibling = pLeftChild;
			node->pRightSibling->pLeftSibling = node;
			pLeftChild = node;
		}
	}
	else
	{
		node->pParent = this;

		if (pLeftChild == NULL)
		{
			pLeftChild = node;
		}
		else
		{
			node->pRightSibling = pLeftChild;
			node->pRightSibling->pLeftSibling = node;
			pLeftChild = node;
		}
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