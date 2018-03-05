#include "Character.h"

Character::Character(Transform* transform, Appearance* appearance, ParticleModel * particle):GameObject(transform, appearance, particle)
{
	mMovementSpeed = 500.0f;
}

void Character::MoveRight(float deltaTime)
{
	//mParticleModel->AddForce()
	mTransform->SetPosition(mTransform->GetPosition().x + mMovementSpeed *deltaTime, mTransform->GetPosition().y, mTransform->GetPosition().z);
}

void Character::MoveLeft(float deltaTime)
{
	mTransform->SetPosition(mTransform->GetPosition().x - mMovementSpeed*deltaTime, mTransform->GetPosition().y, mTransform->GetPosition().z);
}

void Character::MoveForward(float deltaTime)
{
	mTransform->SetPosition(mTransform->GetPosition().x , mTransform->GetPosition().y, mTransform->GetPosition().z + mMovementSpeed*deltaTime);
}

void Character::MoveBackward(float deltaTime)
{
	mTransform->SetPosition(mTransform->GetPosition().x, mTransform->GetPosition().y, mTransform->GetPosition().z - mMovementSpeed*deltaTime);
}
