#include "Level2Enemy.h"

Level2Enemy::Level2Enemy(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider * collider, Vector3D forward)
	:AICharacter(name, transform, appearance, particle,collider,forward)
{
	ChangeState(new StateFindClosestBall());
	mHeldBall = nullptr;
}


Level2Enemy::~Level2Enemy()
{
}

bool Level2Enemy::CollisionEvent(GameObject * collidedWith)
{
	if (collidedWith->GetName() == "Ball")
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

void Level2Enemy::Interact()
{
	if (mHeldBall && mTransform->GetPosition().z < -400.0f)
	{
		ParticleModel* physicsComponent = new ParticleModel(mBallsPhysicsComponent->GetMass(), mForward, mHeldBall->GetTransform());
		Sphere* collider = new Sphere(mHeldBall->GetTransform(), 10.0f);
		mHeldBall->SetPhysicsComponent(physicsComponent);
		Vector3D velocity = (mForward*3000.0f);
		velocity.y += 200.0f;
		mHeldBall->GetPhysicsComponent()->SetVelocity(velocity);
		mHeldBall->SetCollider(collider);

		pParent->AddChild(mHeldBall);
		mHeldBall->GetTransform()->SetPosition(GetTransform()->GetPosition() + mForward*100.0f);

		mHeldBall = nullptr;
	}
}

void Level2Enemy::MoveRight(float deltaTime, float scale)
{
	mPhysicsComponent->AddForce(mRight * scale  * mMovementSpeed);
}

void Level2Enemy::MoveForward(float deltaTime, float scale)
{
	mPhysicsComponent->AddForce(mForward * scale  * mMovementSpeed);
}
