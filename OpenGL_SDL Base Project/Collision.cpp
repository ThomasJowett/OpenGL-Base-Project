#include "Collision.h"

std::vector<Contact> Collision::DetectCollisions(std::vector<GameObject*> gameObjects)
{
	std::vector<Contact>contacts;
	for (int i = 0; i < (int)gameObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < (int)gameObjects.size(); j++)
		{
			 
			if (gameObjects[i]->GetCollider() != nullptr && gameObjects[j]->GetCollider() != nullptr)
			{
				Vector3D contactNormal;
				float penetrationDepth;

				if (gameObjects[i]->GetCollider()->CheckCollision(gameObjects[j]->GetCollider(), contactNormal, penetrationDepth))
				{
					contacts.push_back({ gameObjects[i], gameObjects[j], contactNormal, penetrationDepth });
				}
			}
		}
	}
	return contacts;
}

void Collision::ResolveCollisions(std::vector<Contact> contacts)
{
	for (auto contact : contacts)
	{
		Vector3D velocityA;
		Vector3D velocityB;
		float massA = 0.0f;
		float massB = 0.0f;

		bool moveFirst, moveSecond;

		if(!contact.first->CollisionEvent(contact.second) || !contact.second->CollisionEvent(contact.first))
			return;

		if (contact.first->GetPhysicsComponent() != nullptr)
		{
			velocityA = contact.first->GetPhysicsComponent()->GetVelocity();
			massA = contact.first->GetPhysicsComponent()->GetMass();
			moveFirst = true;
		}
		else
			moveFirst = false;

		if (contact.second->GetPhysicsComponent() != nullptr)
		{
			velocityB = contact.second->GetPhysicsComponent()->GetVelocity();
			massB = contact.second->GetPhysicsComponent()->GetMass();
			moveSecond = true;
		}
		else
			moveSecond = false;

		//play the bounce sound effect if it is a ball colliding
		if (contact.second->GetName() == "Ball" || contact.first->GetName() == "Ball")
		{
			if(velocityA.GetSqrMagnitude() > 10000.0f || velocityB.GetSqrMagnitude() > 10000.0f)
				SoundManager::GetInstance()->PlaySoundEffect("SFX/Bounce.wav", 1, 0);
		}

		if (!moveFirst && !moveSecond)
		{
			//do nothing
			return;
		}
		else if (moveFirst && moveSecond)
		{
			//resolve interpenetration
			contact.first->GetTransform()->SetPosition(contact.first->GetTransform()->GetPosition() + (((contact.contactNormal*(contact.penetrationDepth)) * (massB / massA + massB))/1000));
			contact.second->GetTransform()->SetPosition(contact.second->GetTransform()->GetPosition() + (((contact.contactNormal*-(contact.penetrationDepth)) * (massA / massA + massB))/1000));

			//coeffiecient of restitution hard coded as 1.0
			float coeffiecientOfRestitution = 1.0f;
			contact.first->GetPhysicsComponent()->SetVelocity(((velocityA*massA) + (velocityB*massB) + ((velocityB - velocityA)*(massB*coeffiecientOfRestitution)))/ (massA + massB));
			contact.second->GetPhysicsComponent()->SetVelocity(((velocityA*massA) + (velocityB*massB) + ((velocityA - velocityB)*(massA*coeffiecientOfRestitution))) / (massA + massB));
		}
		else if (moveFirst && !moveSecond)
		{
			//move only first
			contact.first->GetTransform()->SetPosition(contact.first->GetTransform()->GetPosition() + (contact.contactNormal*contact.penetrationDepth));

			contact.first->GetPhysicsComponent()->SetVelocity(Vector3D::Reflect(contact.first->GetPhysicsComponent()->GetVelocity(), contact.contactNormal)* 0.8f);
		}
		else if (!moveFirst && moveSecond)
		{
			//move only second
			contact.second->GetTransform()->SetPosition(contact.second->GetTransform()->GetPosition() + (contact.contactNormal*contact.penetrationDepth));

			contact.second->GetPhysicsComponent()->SetVelocity(Vector3D::Reflect(contact.second->GetPhysicsComponent()->GetVelocity(), contact.contactNormal)* 0.8f);
		}
	}
}
