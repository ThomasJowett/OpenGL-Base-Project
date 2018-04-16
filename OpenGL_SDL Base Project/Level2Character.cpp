#include "Level2Character.h"



Level2Character::Level2Character(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward)
	:Character(name, transform, appearance, particle, collider, forward)
{
	mHeldBall = nullptr;
}


Level2Character::~Level2Character()
{
}

bool Level2Character::CollisionEvent(GameObject * collidedWith)
{
	if (collidedWith->GetName() == "Ball" )
	{
		if (mHeldBall == nullptr)
		{
			if (collidedWith->GetPhysicsComponent()->GetVelocity().GetSqrMagnitude() <= 1000.0f)
			{
				mHeldBall = collidedWith;
				mBallsPhysicsComponent = mHeldBall->GetPhysicsComponent();
				mBallsCollider = mHeldBall->GetCollider();
				mHeldBall->SetPhysicsComponent(nullptr);
				mHeldBall->SetCollider(nullptr);
				AddChild(mHeldBall);
				mHeldBall->GetTransform()->SetPosition({ 20.0f , 0.0f, 20.0f });
			}
			else
			{
				std::cout << collidedWith->GetPhysicsComponent()->GetVelocity().GetSqrMagnitude() << std::endl;
			}
		}
		return false;
	}

	return true;
}

void Level2Character::Interact()
{
	if (mHeldBall && mTransform->GetPosition().z < -400.0f)
	{
		ParticleModel* physicsComponent = new ParticleModel(mBallsPhysicsComponent->GetMass(), mTransform->GetRotation() * mForward, mHeldBall->GetTransform());
		Sphere* collider = new Sphere(mHeldBall->GetTransform(), 10.0f);
		mHeldBall->SetPhysicsComponent(physicsComponent);
		Vector3D velocity = (mTransform->GetRotation() * mForward*3000.0f);
		velocity.y += 200.0f;
		mHeldBall->GetPhysicsComponent()->SetVelocity(velocity);
		mHeldBall->SetCollider(collider);

		pParent->AddChild(mHeldBall);
		mHeldBall->GetTransform()->SetPosition(GetTransform()->GetPosition() + mTransform->GetRotation() * mForward*100.0f);

		mHeldBall = nullptr;
	}
}
