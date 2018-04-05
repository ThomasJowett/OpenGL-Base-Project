#include "ParticleModel.h"

ParticleModel::ParticleModel(float mass, Vector3D velocity, Transform * transform)
	: mMass(mass), mVelocity(velocity), mTransform(transform)
{
	if (mass <= 0)
		mSimulatePhysics = false;

	mDragCoefficient = 1.05;
}

ParticleModel::~ParticleModel()
{
}

void ParticleModel::AddForce(Vector3D force)
{
	mNetForce += force;
}

void ParticleModel::Update(float deltaTime)
{
	if (mSimulatePhysics)
	{
		AddForce(DragForce());
		AddForce(GravitationalForce());

		Vector3D acceleration = mNetForce / mMass;

		mTransform->SetPosition(mTransform->GetPosition() + (mVelocity*deltaTime) + (acceleration*(deltaTime*deltaTime)) / 2);

		mVelocity += (acceleration * deltaTime);
	}

	mNetForce = Vector3D{ 0.0f, 0.0f,0.0f };
}

Vector3D ParticleModel::DragForce()
{
	return mVelocity * -mDragCoefficient;
}

Vector3D ParticleModel::GravitationalForce()
{
	Vector3D gravity = { 0.0f, -980.665f, 0.0f };
	return   gravity * mMass;
}
