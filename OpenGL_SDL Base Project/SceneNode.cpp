#include "SceneNode.h"

SceneNode::SceneNode()
{
	mKeepMatrix = false;
	pParent = NULL;
	pLeftChild = NULL;
	pRightSibling = NULL;
	pLeftSibling = NULL;

	mTransform = new Transform();
}

SceneNode::SceneNode(Transform* transform):mTransform(transform)
{
	mKeepMatrix = false;
	pParent = NULL;
	pLeftChild = NULL;
	pRightSibling = NULL;
	pLeftSibling = NULL;
}

SceneNode::~SceneNode()
{
	RemoveSelf();
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

void SceneNode::RemoveSelf()
{
	//Deal with parents and siblings
	if (pParent != NULL)
	{
		if (pParent->pLeftChild == this)
		{
			pParent->pLeftChild = pRightSibling;
		}

		if (pLeftSibling != NULL)
		{
			pLeftSibling->pRightSibling = pRightSibling;

			if (pRightSibling != NULL)
			{
				pRightSibling->pLeftSibling = pLeftSibling;
			}
		}
	}

	//Deal with children
	if (pLeftChild != NULL)
	{
		pLeftChild->pParent = pParent;
		SceneNode* rightSibling = pLeftChild->pRightSibling;
		while (rightSibling)
		{
			rightSibling->pParent = pParent;
			rightSibling = rightSibling->pRightSibling;
		}
	}

	pParent = nullptr;
	pRightSibling = nullptr;
	pLeftChild = nullptr;
	pLeftSibling = nullptr;
}

void SceneNode::RemoveSelfAndChildren()
{
	//Deal with parents and siblings
	if (pParent != NULL)
	{
		if (pParent->pLeftChild == this)
		{
			pParent->pLeftChild = pRightSibling;
		}

		if (pLeftSibling != NULL)
		{
			pLeftSibling->pRightSibling = pRightSibling;

			if (pRightSibling != NULL)
			{
				pRightSibling->pLeftSibling = pLeftSibling;
			}
		}
	}

	pParent = nullptr;
	pRightSibling = nullptr;
	pLeftChild = nullptr;
	pLeftSibling = nullptr;
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

Transform SceneNode::GetWorldTransform() const
{
	SceneNode* parent = pParent;
	Transform transform = *mTransform;
	while (parent)
	{
		transform += *parent->GetTransform();
		parent = parent->pParent;
	}
	return transform;
}
