#include "GameObject.h"

GameObject::GameObject(std::string name, Transform * transform, Appearance * appearance, ParticleModel * particle, Collider* collider)
	: mName(name), SceneNode(transform), mAppearance(appearance), mPhysicsComponent(particle), mCollider(collider)
{
}

void GameObject::Update(float deltaTime)
{
	if (mPhysicsComponent)
		mPhysicsComponent->Update(deltaTime);
}

void GameObject::Render(Shader* shader)
{
	SceneNode::Render(shader);

	if(mAppearance)
		mAppearance->Render(shader);
}

bool GameObject::CollisionEvent(GameObject* collidedWith)
{
	return true;
}
