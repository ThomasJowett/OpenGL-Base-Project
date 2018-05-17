#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "GameObject.h"
#include "iInput.h"

class Character : public GameObject , public iInput
{
public:
	Character(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward);

	virtual bool CollisionEvent(GameObject* collidedWith) override;
	void MoveRight(float scale) override;
	void MoveForward(float scale) override;

	void Yaw(float scale)override;
	void Pitch(float scale)override;
	void Roll(float scale)override;

	virtual void Interact();

	bool mInheritRoll = false, mInheritPitch = false, mInheritYaw = false;
protected:
	float mMovementSpeed;
	Vector3D mForward;
	Vector3D mRight;
	Vector3D mUp;
};
#endif // !_CHARACTER_H

