#ifndef _OBJECT3DS_H_
#define _OBJECT3DS_H_
#include "Commons.h"
#include <string>

#include "Transform.h"
#include "Appearance.h"
#include "ParticleModel.h"
#include "SceneNode.h"

using::std::string;
class Texture;

class GameObject : public SceneNode
{
public:
	GameObject(std::string name, Transform* transform, Appearance* appearance, ParticleModel * particle, Collider* collider);
	~GameObject() {}

	virtual void Update(float deltaTime);
	void Render() override;

	

	void SetAppearance(Appearance * appearance) { mAppearance = appearance; }
	Appearance * GetAppearance() const { return mAppearance; }

	void SetPhysicsComponent(ParticleModel * physicsComponent) { mPhysicsComponent = physicsComponent; }
	ParticleModel * GetPhysicsComponent() const { return mPhysicsComponent; }

	void SetCollider(Collider * collider) { mCollider = collider; }
	Collider * GetCollider() const { return mCollider; }

	virtual bool CollisionEvent(GameObject* collidedWith);

	std::string GetName()const { return mName; }
	void SetName(std::string name) { mName = name; }

protected:
	std::string mName;
	Appearance * mAppearance;
	ParticleModel * mPhysicsComponent;
	Collider * mCollider;
};


#endif // !_OBJECT3DS_H_
