#ifndef _PARTICLEMODEL_H
#define _PARTICLEMODEL_H

#include "Vector.h"
#include "Transform.h"
#include "Collider.h"

class ParticleModel
{
public:
	ParticleModel(float mass, Vector3D velocity, Transform * transform, float radius);
	~ParticleModel();

	void AddForce(Vector3D force);

	void Update(float deltaTime);

	Vector3D GetVelocity() const { return mVelocity; }
	void SetVelocity(Vector3D velocity) { mVelocity = velocity; }
	Vector3D GetNetForce() const { return mNetForce; }

	float GetMass() const { return mMass; }
	void SetMass(float mass) { mMass = mass; }

	Sphere* GetBoundingSphere() const { return mBoundingSphere; }
	
	void SetDragCoefficient(float drag) { mDragCoefficient = drag; }

private:
	Transform * mTransform;
	Vector3D mVelocity;
	Vector3D mNetForce;
	float mMass;
	bool mSimulatePhysics;
	float mDragCoefficient;

	Sphere* mBoundingSphere;

	Vector3D DragForce();
	Vector3D GravitationalForce();
};
#endif //!_PARTICLEMODEL_H

