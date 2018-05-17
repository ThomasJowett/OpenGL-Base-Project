#include "Character.h"

Character::Character(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward)
	:GameObject(name, transform, appearance, particle, collider), mForward(forward.GetNormalized())
{
	mMovementSpeed = 100000.0f;
	mUp = { 0.0f, 1.0f, 0.0f };
	mRight = Vector3D::Cross(mForward, mUp);
	mUp = Vector3D::Cross(mForward, mRight);

	mPhysicsComponent->SetDragCoefficient(100.0f);
}

bool Character::CollisionEvent(GameObject* collidedWith)
{
	return true;
}

void Character::MoveRight(float scale)
{
	mPhysicsComponent->AddForce((mTransform->GetRotation() * mRight) * scale  * mMovementSpeed);
}

void Character::MoveForward(float scale)
{
	mPhysicsComponent->AddForce((mTransform->GetRotation() * mForward) * scale  * mMovementSpeed);
}

void Character::Yaw(float scale)
{
	//rotate quaternion about up vector
}

void Character::Pitch(float scale)
{
	//rotate quaternion about right vector
}

void Character::Roll(float scale)
{
	//rotate quaternion about forward vector
}

void Character::Interact()
{
	std::cout << "interact";
}
