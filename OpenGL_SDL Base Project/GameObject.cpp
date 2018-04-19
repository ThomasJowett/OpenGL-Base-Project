#include "GameObject.h"
#include "../gl/glut.h"
#include "3DSLoader.h"
#include "OBJLoader.h"
#include "SDL.h"
#include "SoundManager.h"

GameObject::GameObject(std::string name, Transform * transform, Appearance * appearance, ParticleModel * particle, Collider* collider)
	: mName(name), SceneNode(transform), mAppearance(appearance), mPhysicsComponent(particle), mCollider(collider)
{
}

void GameObject::Update(float deltaTime)
{
	if (mPhysicsComponent)
		mPhysicsComponent->Update(deltaTime);
}

void GameObject::Render()
{
	SceneNode::Render();

	if(mAppearance)
		mAppearance->Render();
}

bool GameObject::CollisionEvent(GameObject* collidedWith)
{
	return true;
}
