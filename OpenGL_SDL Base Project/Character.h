#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "GameObject.h"
#include "iInput.h"

class Character : public GameObject , public iInput
{
public:
	Character(Transform* transform, Appearance* appearance, ParticleModel * particle);
	void MoveRight(float deltaTime) override;
	void MoveLeft(float deltaTime) override;
	void MoveForward(float deltaTime) override;
	void MoveBackward(float deltaTime) override;
private:
	float mMovementSpeed;
};
#endif // !_CHARACTER_H

