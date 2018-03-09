#include "Character.h"

Character::Character(Transform* transform, Appearance* appearance, ParticleModel * particle):GameObject(transform, appearance, particle)
{
	mMovementSpeed = 10000.0f;
	mForward = { 0.0f, 0.0f, 1.0f };
	mRight = { 1.0f, 0.0f, 0.0f };
	mUp = { 0.0f, 1.0f, 0.0f };

	mParticleModel->SetDragCoefficient(1000.0f);
}

void Character::MoveRight(float deltaTime, float scale)
{
	mParticleModel->AddForce(mForward * scale  * mMovementSpeed);
	//mTransform->SetPosition(mTransform->GetPosition().x + mMovementSpeed *deltaTime, mTransform->GetPosition().y, mTransform->GetPosition().z);
}

void Character::MoveForward(float deltaTime, float scale)
{
	mParticleModel->AddForce(mRight * scale  * mMovementSpeed);
	//mTransform->SetPosition(mTransform->GetPosition().x , mTransform->GetPosition().y, mTransform->GetPosition().z + mMovementSpeed*deltaTime);
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
