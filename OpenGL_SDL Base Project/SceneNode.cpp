#include "SceneNode.h"

SceneNode::SceneNode()
{
	mKeepMatrix = false;
	pParent = nullptr;
	pLeftChild = nullptr;
	pRightSibling = nullptr;
	pLeftSibling = nullptr;

	mTransform = new Transform();
}

SceneNode::SceneNode(Transform* transform):mTransform(transform)
{
	mKeepMatrix = false;
	pParent = nullptr;
	pLeftChild = nullptr;
	pRightSibling = nullptr;
	pLeftSibling = nullptr;
}

SceneNode::~SceneNode()
{
	RemoveSelf();
}

void SceneNode::AddChild(SceneNode *node)
{
	//if the node to be attached has a parent deal with the old reference
	if (node->pParent != nullptr)
	{
		if (node->pParent->pLeftChild == node)
		{
			node->pParent->pLeftChild = node->pRightSibling;
		}

		if (node->pLeftSibling != nullptr)
		{
			node->pLeftSibling->pRightSibling = node->pRightSibling;

			if (node->pRightSibling != nullptr)
			{
				node->pRightSibling->pLeftSibling = node->pLeftSibling;
			}
		}
	}

	//if this node has children then move them down the list
	if (pLeftChild != nullptr)
	{
		pLeftChild->pLeftSibling = node;
	}

	//setup the new nodes references
	node->pLeftSibling = nullptr;
	node->pParent = this;
	node->pRightSibling = pLeftChild;
	pLeftChild = node;
}

void SceneNode::RemoveSelf()
{
	//Deal with parents and siblings
	if (pParent != nullptr)
	{
		if (pParent->pLeftChild == this)
		{
			pParent->pLeftChild = pRightSibling;
		}

		if (pLeftSibling != nullptr)
		{
			pLeftSibling->pRightSibling = pRightSibling;

			if (pRightSibling != nullptr)
			{
				pRightSibling->pLeftSibling = pLeftSibling;
			}
		}
	}

	//Deal with children
	if (pLeftChild != nullptr)
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
	if (pParent != nullptr)
	{
		if (pParent->pLeftChild == this)
		{
			pParent->pLeftChild = pRightSibling;
		}

		if (pLeftSibling != nullptr)
		{
			pLeftSibling->pRightSibling = pRightSibling;

			if (pRightSibling != nullptr)
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

void SceneNode::Render(Shader* shader)
{
	mTransform->UpdateWorldMatrix();
	shader->UpdateWorld(mTransform);
}

void SceneNode::Traverse(Shader* shader)
{
	//TODO: use with buffers
	if (!mKeepMatrix)
	{
		//glPushMatrix();
	}

	Render(shader);
	if (pLeftChild != nullptr)
		pLeftChild->Traverse(shader);
	if (!mKeepMatrix)
	{
		//glPopMatrix();
	}
	if (pRightSibling != nullptr)
		pRightSibling->Traverse(shader);
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
