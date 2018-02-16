#ifndef _OBJECT3DS_H_
#define _OBJECT3DS_H_
#include "Commons.h"
#include <string>
#include "Texture2D.h"
#include "Transform.h"
#include "Appearance.h"
#include "ParticleModel.h"
#include "SceneNode.h"
#include "Collision.h"

using::std::string;
class Texture;

class GameObject : public SceneNode
{
public:
	GameObject(Transform* transform, Appearance* appearance, ParticleModel * particle, float boundingRadius);
	~GameObject() {}

	void Update(float deltaTime);
	void Render();

	void SetTransform(Transform * transform) { mTransform = transform; }
	Transform * GetTransform() const { return mTransform; }

	void SetAppearance(Appearance * appearance) { mAppearance = appearance; }
	Appearance * GetAppearance() const { return mAppearance; }

	void SetBoundingSphere(Sphere * sphere) { mBoundingSphere = sphere; }
	Sphere * GetBoundingSphere() const { return mBoundingSphere; }

	void SetParticleModel(ParticleModel * particleModel) { mParticleModel = particleModel; }
	ParticleModel * GetParticleModel() const { return mParticleModel; }

private:
	Transform * mTransform;
	Appearance * mAppearance;
	ParticleModel * mParticleModel;

	Sphere * mBoundingSphere;

	char fileName[20];
	char fileType[3];
	char textureName[20];
};


#endif // !_OBJECT3DS_H_
