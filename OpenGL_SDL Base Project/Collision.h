#ifndef _COLLISION_H
#define _COLLISION_H

#include "GameObject.h"
#include <vector>

struct Contact
{
	GameObject* first;
	GameObject* second;
	Vector3D contactNormal;
	float penetrationDepth;
};

class Collision {
public:
	static float SphereSphereCollision(Sphere * sphere1, Sphere * sphere2) {
		Vector3D centre1 = sphere1->GetTransform()->GetPosition();
		Vector3D centre2 = sphere2->GetTransform()->GetPosition();
		
		Vector3D distance = centre2 - centre1;

		float sumOfBoundingRadii = sphere1->GetBoundingRadius() + sphere2->GetBoundingRadius();
		return sumOfBoundingRadii - distance.GetMagnitude();
	}
	/*
	static bool AABBAABBCollision(AABB* box1, AABB* box2) {
		if (box1->GetXMax() < box2->GetXMin()
			|| box1->GetXMin() > box2->GetXMax()
			|| box1->GetYMax() < box2->GetYMin()
			|| box1->GetYMin() > box2->GetYMax()
			|| box1->GetZMax() < box2->GetZMin()
			|| box1->GetZMin() > box2->GetZMax())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	static bool SphereAABBCollision(Sphere* sphere, AABB* box) {
		if (box->GetXMax<(sphere->GetTransform()->GetPosition().x - sphere->GetBoundingRadius())
			|| box->GetXMin>(sphere->GetTransform()->GetPosition().x + sphere->GetBoundingRadius())
			|| box->GetYMax < sphere->GetTransform()->GetPosition().y - sphere->GetBoundingRadius()
			|| box->GetYMin > sphere->GetTransform()->GetPosition().y + sphere->GetBoundingRadius()
			|| box->GetZMax < sphere->GetTransform()->GetPosition().z - sphere->GetBoundingRadius()
			|| box->GetZMin > sphere->GetTransform()->GetPosition().z + sphere->GetBoundingRadius())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	*/
	static std::vector<Contact> DetectCollisions(std::vector<GameObject*>gameObjects);

	static void ResolveCollisions(std::vector<Contact>contacts);
};

#endif // !_COLLISION_H
