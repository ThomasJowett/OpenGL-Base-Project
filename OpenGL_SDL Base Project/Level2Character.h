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

	int GetTimesHit()const { return mTimesHit;}
private:
	GameObject* mHeldBall;
	ParticleModel* mBallsPhysicsComponent;
	Collider* mBallsCollider;
	int mTimesHit = 0;
};

