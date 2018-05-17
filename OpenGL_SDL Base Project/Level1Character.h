#pragma once
#include "Character.h"
class Level1Character : public Character
{
public:
	Level1Character(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward);
	~Level1Character();

	bool CollisionEvent(GameObject* collidedWith)override;

	void MoveRight(float scale) override;
	void MoveForward(float scale) override;

	void Yaw(float scale) override;
	void Pitch(float scale) override;
	void Roll(float scale) override;

	int GetLives() const { return mLives; }
private:
	int mLives = 4;
};

