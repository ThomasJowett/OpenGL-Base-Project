#include "GameObject.h"
#include "../gl/glut.h"
#include "3DSLoader.h"
#include "OBJLoader.h"
#include "SDL.h"

GameObject::GameObject(Transform * transform, Appearance * appearance, float boundingRadius) : mTransform(transform), mAppearance(appearance)
{
	mBoundingSphere = new Sphere(mTransform->GetPosition(), boundingRadius);
}

void GameObject::Update(float deltaTime)
{
	
}

void GameObject::Render()
{
	if (mTransform)
		mTransform->UpdateWorldMatrix();

	mAppearance->Render();
}