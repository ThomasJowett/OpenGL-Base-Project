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
	pLeftSibling = NULL;
	pParent = NULL;
}

void SceneNode::AddChild(SceneNode *node)
{
	//if the node to be attached has a parent deal with the old reference
	if (node->pParent != NULL)
	{
		if (node->pParent->pLeftChild == node)
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
	}

	//if this node has children then move them down the list
	if (pLeftChild != NULL)
	{
		pLeftChild->pLeftSibling = node;
	}

	//setup the new nodes references
	node->pLeftSibling = NULL;
	node->pParent = this;
	node->pRightSibling = pLeftChild;
	pLeftChild = node;
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