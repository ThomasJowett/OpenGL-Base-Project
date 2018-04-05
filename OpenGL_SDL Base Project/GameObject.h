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
	void Render();

	void SetTransform(Transform * transform) { mTransform = transform; }
	Transform * GetTransform() const { return mTransform; }

	void SetAppearance(Appearance * appearance) { mAppearance = appearance; }
	Appearance * GetAppearance() const { return mAppearance; }

	void SetParticleModel(ParticleModel * particleModel) { mParticleModel = particleModel; }
	ParticleModel * GetPhysicsComponent() const { return mParticleModel; }

	void SetCollider(Collider * collider) { mCollider = collider; }
	Collider * GetCollider() const { return mCollider; }

	virtual void CollisionEvent(GameObject* collidedWith);

	std::string GetName()const { return mName; }
	void SetName(std::string name) { mName = name; }

protected:
	std::string mName;
	Transform * mTransform;
	Appearance * mAppearance;
	ParticleModel * mParticleModel;
	Collider * mCollider;
};


#endif // !_OBJECT3DS_H_
