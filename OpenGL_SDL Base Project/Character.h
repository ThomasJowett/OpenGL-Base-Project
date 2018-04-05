#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "GameObject.h"
#include "iInput.h"

class Character : public GameObject , public iInput
{
public:
	Character(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider);

	void CollisionEvent(GameObject* collidedWith) override;
	void MoveRight(float deltaTime, float scale) override;
	void MoveForward(float deltaTime, float scale) override;

	void Yaw(float deltaTime, float scale);
	void Pitch(float deltaTime, float scale);
	void Roll(float deltaTime, float scale);

	void Interact();
private:
	float mMovementSpeed;
	Vector3D mForward;
	Vector3D mRight;
	Vector3D mUp;

	int mLives = 3;
};
#endif // !_CHARACTER_H

