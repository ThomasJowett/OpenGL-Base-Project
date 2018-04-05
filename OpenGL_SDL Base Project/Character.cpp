#include "Character.h"

Character::Character(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider)
	:GameObject(name, transform, appearance, particle, collider)
{
	mMovementSpeed = 100000.0f;
	mForward = { 0.0f, 0.0f, 1.0f };
	mRight = { 1.0f, 0.0f, 0.0f };
	mUp = { 0.0f, 1.0f, 0.0f };

	mPhysicsComponent->SetDragCoefficient(100.0f);
}

void Character::CollisionEvent(GameObject* collidedWith)
{
	if (Sphere* otherSphere = dynamic_cast<Sphere*>(collidedWith->GetCollider()))
	{
		collidedWith->SetPhysicsComponent(nullptr);
		collidedWith->SetCollider(nullptr);
		//std::cout << collidedWith->GetName();

		AddChild(collidedWith);
		collidedWith->GetTransform()->SetPosition({ 0.0f, 0.0f, -50.0f * (4-mLives) });
		mLives--;
	}
}

void Character::MoveRight(float deltaTime, float scale)
{
	mPhysicsComponent->AddForce(mForward * scale  * mMovementSpeed);
}

void Character::MoveForward(float deltaTime, float scale)
{
	mPhysicsComponent->AddForce(mRight * scale  * mMovementSpeed);
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
