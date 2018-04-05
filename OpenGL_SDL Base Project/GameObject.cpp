#include "GameObject.h"
#include "../gl/glut.h"
#include "3DSLoader.h"
#include "OBJLoader.h"
#include "SDL.h"
#include "SoundManager.h"

GameObject::GameObject(std::string name, Transform * transform, Appearance * appearance, ParticleModel * particle, Collider* collider)
	: mName(name), mTransform(transform), mAppearance(appearance), mParticleModel(particle), mCollider(collider)
{
}

void GameObject::Update(float deltaTime)
{
	if (mParticleModel)
		mParticleModel->Update(deltaTime);
}

void GameObject::Render()
{
	if (mTransform)
		mTransform->UpdateWorldMatrix();

	if(mAppearance)
		mAppearance->Render();
}

void GameObject::CollisionEvent(GameObject* collidedWith)
{
	//std::cout << collidedWith->GetName() << std::endl;
	SoundManager::GetInstance()->PlaySoundEffect("SFX/Bounce.wav", -1, 0);
}
