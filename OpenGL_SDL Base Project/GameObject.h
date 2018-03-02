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
	GameObject(Transform* transform, Appearance* appearance, ParticleModel * particle);
	~GameObject() {}

	void Update(float deltaTime);
	void Render();

	void SetTransform(Transform * transform) { mTransform = transform; }
	Transform * GetTransform() const { return mTransform; }

	void SetAppearance(Appearance * appearance) { mAppearance = appearance; }
	Appearance * GetAppearance() const { return mAppearance; }

	void SetParticleModel(ParticleModel * particleModel) { mParticleModel = particleModel; }
	ParticleModel * GetParticleModel() const { return mParticleModel; }

private:
	Transform * mTransform;
	Appearance * mAppearance;
	ParticleModel * mParticleModel;

	char fileName[20];
	char fileType[3];
	char textureName[20];
};


#endif // !_OBJECT3DS_H_
