#include "Level1Character.h"



Level1Character::Level1Character(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward)
	:Character(name,transform, appearance, particle, collider, forward)
{
}


Level1Character::~Level1Character()
{
}

bool Level1Character::CollisionEvent(GameObject * collidedWith)
{
	if (Sphere* otherSphere = dynamic_cast<Sphere*>(collidedWith->GetCollider()))
	{
		collidedWith->SetPhysicsComponent(nullptr);
		collidedWith->SetCollider(nullptr);

		AddChild(collidedWith);
		collidedWith->GetTransform()->SetPosition({ 0.0f, 0.0f, (-50.0f * (5 - mLives)) - 50.0f });
		mLives--;
		return false;
	}

	return true;
}

void Level1Character::MoveRight(float scale)
{
	mPhysicsComponent->AddForce(mForward * scale  * mMovementSpeed);
}

void Level1Character::MoveForward(float scale)
{
	mPhysicsComponent->AddForce(mRight * scale  * mMovementSpeed * -1.0f);
}

void Level1Character::Yaw(float scale)
{
}

void Level1Character::Pitch(float scale)
{
}

void Level1Character::Roll(float scale)
{
}
