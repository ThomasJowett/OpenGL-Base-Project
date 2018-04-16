#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "GameObject.h"
#include "iInput.h"

class Character : public GameObject , public iInput
{
public:
	Character(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward);

	virtual bool CollisionEvent(GameObject* collidedWith) override;
	void MoveRight(float deltaTime, float scale) override;
	void MoveForward(float deltaTime, float scale) override;

	void Yaw(float deltaTime, float scale);
	void Pitch(float deltaTime, float scale);
	void Roll(float deltaTime, float scale);

	virtual void Interact();

	bool mInheritRoll = false, mInheritPitch = false, mInheritYaw = false;
protected:
	float mMovementSpeed;
	Vector3D mForward;
	Vector3D mRight;
	Vector3D mUp;
};
#endif // !_CHARACTER_H

