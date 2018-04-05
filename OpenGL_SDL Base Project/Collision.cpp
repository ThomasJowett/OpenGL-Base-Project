#include "Collision.h"

std::vector<Contact> Collision::DetectCollisions(std::vector<GameObject*> gameObjects)
{
	std::vector<Contact>contacts;
	for (int i = 0; i < gameObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < gameObjects.size(); j++)
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
		//std::cout << contact.contactNormal.x << "," << contact.contactNormal.y << "," << contact.contactNormal.z << std::endl;
		Vector3D velocityA;
		Vector3D velocityB;
		float massA = 0.0f;
		float massB = 0.0f;

		bool moveFirst, moveSecond;

		contact.first->CollisionEvent(contact.second);
		contact.second->CollisionEvent(contact.first);

		if (contact.first->GetName() == "Denzel" && contact.second->GetName() == "Ball")
			//move the ball to the list of balls following denzel
		{
			std::cout << contact.contactNormal.x << "," << contact.contactNormal.y << "," << contact.contactNormal.z << std::endl;
		}

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

		if (!moveFirst && !moveSecond)
		{
			//do nothing
			return;
		}
		else if (moveFirst && moveSecond)
		{
			//resolve interpenetration
			contact.first->GetTransform()->SetPosition(contact.first->GetTransform()->GetPosition() + ((contact.contactNormal*(contact.penetrationDepth)) * (massB / massA + massB)));
			contact.second->GetTransform()->SetPosition(contact.second->GetTransform()->GetPosition() - ((contact.contactNormal*(contact.penetrationDepth)) * (massA / massA + massB)));

			//coeffiecient of restitution hard coded as 0.5
			float coeffiecientOfRestitution = 1.0f;
			contact.first->GetPhysicsComponent()->SetVelocity((velocityA*massA) + (velocityB*massB) + ((velocityB - velocityA)*(massB*coeffiecientOfRestitution)) / (massA + massB));
			contact.second->GetPhysicsComponent()->SetVelocity((velocityA*massA) + (velocityB*massB) + ((velocityA - velocityB)*(massA*coeffiecientOfRestitution)) / (massA + massB));
		}
		else if (moveFirst && !moveSecond)
		{
			//move only first
			contact.first->GetTransform()->SetPosition(contact.first->GetTransform()->GetPosition() + (contact.contactNormal*contact.penetrationDepth));

			contact.first->GetPhysicsComponent()->SetVelocity(Vector3D::Reflect(contact.first->GetPhysicsComponent()->GetVelocity(), contact.contactNormal)* 1.0);
		}
		else if (!moveFirst && moveSecond)
		{
			//move only second
			contact.second->GetTransform()->SetPosition(contact.second->GetTransform()->GetPosition() + (contact.contactNormal*contact.penetrationDepth));

			contact.second->GetPhysicsComponent()->SetVelocity(Vector3D::Reflect(contact.second->GetPhysicsComponent()->GetVelocity(), contact.contactNormal)* 1.0);
		}
	}
}
