#include "Collision.h"

std::vector<Contact> Collision::DetectCollisions(std::vector<GameObject*> gameObjects)
{
	std::vector<Contact>contacts;
	for (int i = 0; i < gameObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < gameObjects.size(); j++)
		{
			 
			if (gameObjects[i]->GetParticleModel() != nullptr && gameObjects[j]->GetParticleModel() != nullptr)
			{
				float penetrationDepth = Collision::SphereSphereCollision(gameObjects[i]->GetParticleModel()->GetBoundingSphere(), gameObjects[j]->GetParticleModel()->GetBoundingSphere());
				if (penetrationDepth > 0.0f)
				{
					Vector3D contactNormal = gameObjects[i]->GetTransform()->GetPosition() - gameObjects[j]->GetTransform()->GetPosition();
					contactNormal.Normalize();

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
		Vector3D velocityA = contact.first->GetParticleModel()->GetVelocity();
		Vector3D velocityB = contact.second->GetParticleModel()->GetVelocity();

		float massA = contact.first->GetParticleModel()->GetMass();
		float massB = contact.second->GetParticleModel()->GetMass();

		//resolve interpenetration
		contact.first->GetTransform()->SetPosition(contact.first->GetTransform()->GetPosition() + ((contact.contactNormal*(contact.penetrationDepth)) * (massB / massA + massB)));
		contact.second->GetTransform()->SetPosition(contact.second->GetTransform()->GetPosition() - ((contact.contactNormal*(contact.penetrationDepth)) * (massA / massA + massB)));

		//coeffiecient of restitution hard coded as 0.5
		float coeffiecientOfRestitution = 0.5f;
		contact.first->GetParticleModel()->SetVelocity((velocityA*massA) + (velocityB*massB) + ((velocityB - velocityA)*(massB*coeffiecientOfRestitution)) / (massA + massB));
		contact.second->GetParticleModel()->SetVelocity((velocityA*massA) + (velocityB*massB) + ((velocityA - velocityB)*(massA*coeffiecientOfRestitution)) / (massA + massB));
	}
}
