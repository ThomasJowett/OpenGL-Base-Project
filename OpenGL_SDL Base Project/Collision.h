#ifndef _COLLISION_H
#define _COLLISION_H

#include "GameObject.h"
#include "SoundManager.h"
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
	static std::vector<Contact> DetectCollisions(std::vector<GameObject*>gameObjects);

	static void ResolveCollisions(std::vector<Contact>contacts);
};

#endif // !_COLLISION_H
