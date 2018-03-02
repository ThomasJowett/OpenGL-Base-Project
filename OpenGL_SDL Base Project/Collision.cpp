#include "Collision.h"

std::vector<Contact*> Collision::DetectCollisions(std::vector<GameObject*> gameObjects)
{
	std::vector<Contact*>contacts;
	for (int i = 0; i < gameObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < gameObjects.size(); j++)
		{
			if (gameObjects[i]->GetParticleModel() != nullptr && gameObjects[j]->GetParticleModel() != nullptr)
				Collision::SphereSphereCollision(gameObjects[i]->GetParticleModel()->GetBoundingSphere(), gameObjects[j]->GetParticleModel()->GetBoundingSphere());
		}
	}
	return contacts;
}

void Collision::ResolveCollisions(std::vector<Contact*> contacts)
{
	for (auto contact : contacts)
	{
		Vector3D velocityA = contact->first->GetParticleModel()->GetVelocity();
		Vector3D velocityB = contact->second->GetParticleModel()->GetVelocity();

		float massA = contact->first->GetParticleModel()->GetMass();
		float massB = contact->second->GetParticleModel()->GetMass();

		//coeffiecient of restitution hard coded as 0.5
		velocityA = ((velocityA*massA) + (velocityB*massB) + ((velocityB - velocityA)*(massB*0.5)) / (massA + massB));
		velocityB = ((velocityA*massA) + (velocityB*massB) + ((velocityB - velocityA)*(massA*0.5)) / (massA + massB));

		contact->first->GetParticleModel()->SetVelocity(velocityA);

		contact->second->GetParticleModel()->SetVelocity(velocityB);
	}
}
