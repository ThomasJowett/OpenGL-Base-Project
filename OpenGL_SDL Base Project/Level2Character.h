#pragma once
#include "Character.h"
class Level2Character :
	public Character
{
public:
	Level2Character(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward);
	~Level2Character();

	bool CollisionEvent(GameObject* collidedWith)override;
	void Interact()override;

	void MoveRight(float deltaTime, float scale) override;
	void MoveForward(float deltaTime, float scale) override;

	void Yaw(float deltaTime, float scale);
	void Pitch(float deltaTime, float scale);
	void Roll(float deltaTime, float scale);
private:
	GameObject* mHeldBall;
	ParticleModel* mBallsPhysicsComponent;
	Collider* mBallsCollider;
};

