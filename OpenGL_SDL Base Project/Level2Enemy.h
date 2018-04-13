#pragma once
#include "AIStateMachine.h"
#include "StateFindClosestBall.h"

class Level2Enemy :
	public AICharacter
{
public:
	Level2Enemy(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward);
	~Level2Enemy();

	bool CollisionEvent(GameObject* collidedWith)override;
	void Interact()override;

	void MoveRight(float deltaTime, float scale) override;
	void MoveForward(float deltaTime, float scale) override;
private:
	GameObject* mHeldBall;
	ParticleModel* mBallsPhysicsComponent;
	Collider* mBallsCollider;
};

