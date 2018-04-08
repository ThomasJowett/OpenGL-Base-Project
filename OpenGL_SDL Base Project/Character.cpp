#include "Character.h"

Character::Character(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward)
	:GameObject(name, transform, appearance, particle, collider), mForward(forward.GetNormalized())
{
	mMovementSpeed = 100000.0f;
	mUp = { 0.0f, 1.0f, 0.0f };
	mRight = Vector3D::Cross(mForward, mUp);

	mPhysicsComponent->SetDragCoefficient(100.0f);
}

bool Character::CollisionEvent(GameObject* collidedWith)
{
	return true;
}

void Character::MoveRight(float deltaTime, float scale)
{
}

void Character::MoveForward(float deltaTime, float scale)
{
	
}

void Character::Yaw(float deltaTime, float scale)
{
}

void Character::Pitch(float deltaTime, float scale)
{
}

void Character::Roll(float deltaTime, float scale)
{
}

void Character::Interact()
{
	std::cout << "interact";
}
