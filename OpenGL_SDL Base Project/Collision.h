#ifndef _COLLISION_H
#define _COLLISION_H

#include "GameObject.h"
#include <vector>

struct Contact
{
	GameObject* first;
	GameObject* second;
};

class Collision {
public:
	static bool SphereSphereCollision(Sphere * sphere1, Sphere * sphere2) {
		Vector3D centre1 = sphere1->GetTransform()->GetPosition();
		Vector3D centre2 = sphere2->GetTransform()->GetPosition();
		
		Vector3D distance = centre2 - centre1;

		float sumOfBoundingRadii = sphere1->GetBoundingRadius() + sphere2->GetBoundingRadius();
		if (distance.GetSqrMagnitude() < (sumOfBoundingRadii * sumOfBoundingRadii)) {
			return true;
		}
		return false;
	}
	
	static std::vector<Contact*> DetectCollisions(std::vector<GameObject*>gameObjects);

	static void ResolveCollisions(std::vector<Contact*>contacts);
};

#endif // !_COLLISION_H
