#pragma once
#include "Character.h"
class Level1Character : public Character
{
public:
	Level1Character(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward);
	~Level1Character();

	bool CollisionEvent(GameObject* collidedWith)override;

	void MoveRight(float deltaTime, float scale) override;
	void MoveForward(float deltaTime, float scale) override;

	void Yaw(float deltaTime, float scale);
	void Pitch(float deltaTime, float scale);
	void Roll(float deltaTime, float scale);

	int GetLives() const { return mLives; }
private:
	int mLives = 4;
};

