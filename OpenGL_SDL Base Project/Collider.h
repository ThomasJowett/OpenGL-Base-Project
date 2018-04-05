#ifndef _COLLIDER_H
#define _COLLIDER_H

#include "Transform.h"

enum CollisionChanel
{
	OVERLAP = 0,
	BLOCK
};

class Collider
{
public:
	Collider(Transform* transform) : mTransform(transform) {}
	~Collider() {}

	void SetTransform(Transform* transform) { mTransform = transform; }
	Transform* GetTransform() { return mTransform; }

	virtual bool CheckCollision(Collider* otherCollider, Vector3D& normal, float& penetrationDepth) = 0;

	Vector3D GetCentre() { return mTransform->GetPosition(); }

	bool TestAxis(Vector3D axis, float minA, float maxA, float minB, float maxB, Vector3D& mtvAxis, float& mtvDistance);

	bool GetCollided() const { return mCollided; }
	void SetCollided(bool collided) { mCollided = collided; }

protected:
	Transform* mTransform;
	bool mCollided;
};

class Sphere : public Collider
{
public:
	Sphere(Transform* transform, float radius) : Collider(transform), mRadius(radius) {}
	float GetBoundingRadius() const { return mRadius; }

	bool CheckCollision(Collider* otherCollider, Vector3D& normal, float& penetrationDepth) override;

private:
	float mRadius;
};

class AABB : public Collider
{
public:
	AABB(Transform* transform, float height, float width, float depth) : mHeight(height), mWidth(width), mDepth(depth) , Collider(transform){}
	float GetXMin() const { return mTransform->GetPosition().x - (mWidth / 2); }
	float GetXMax() const { return mTransform->GetPosition().x + (mWidth / 2); }
	float GetYMin() const { return mTransform->GetPosition().y - (mHeight / 2); }
	float GetYMax() const { return mTransform->GetPosition().y + (mHeight / 2); }
	float GetZMin() const { return mTransform->GetPosition().z - (mDepth / 2); }
	float GetZMax() const { return mTransform->GetPosition().z + (mDepth / 2); }

	bool CheckCollision(Collider* otherCollider, Vector3D& normal, float& penetrationDepth) override;

private:
	float mHeight, mWidth, mDepth;
};

class Plane : public Collider
{
public:
	bool CheckCollision(Collider* otherCollider, Vector3D& normal, float& penetrationDepth) override;
private:
	Vector3D mNormal;
	Vector3D mPosition;
};
#endif // !_COLLIDER_H

