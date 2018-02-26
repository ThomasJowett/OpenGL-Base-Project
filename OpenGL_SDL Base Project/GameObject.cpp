#include "GameObject.h"
#include "../gl/glut.h"
#include "3DSLoader.h"
#include "OBJLoader.h"
#include "SDL.h"

GameObject::GameObject(Transform * transform, Appearance * appearance, ParticleModel * particle) : mTransform(transform), mAppearance(appearance), mParticleModel(particle)
{
}

void GameObject::Update(float deltaTime)
{
	if (mParticleModel != nullptr)
		mParticleModel->Update(deltaTime);
}

void GameObject::Render()
{
	if (mTransform)
		mTransform->UpdateWorldMatrix();

	mAppearance->Render();
}