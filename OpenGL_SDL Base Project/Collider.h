#ifndef _COLLIDER_H
#define _COLLIDER_H

#include "Transform.h"

class Sphere {
public:
	Sphere(Transform* transform, float radius) : mTransform(transform), mRadius(radius) {}
	float GetBoundingRadius() const { return mRadius; }
	Transform* GetTransform() { return mTransform; }

private:
	Transform* mTransform;
	float mRadius;
};

class AABB {
public:
	AABB(Transform* transform, float height, float width, float depth) : mHeight(height), mWidth(width), mDepth(depth) {}
	Transform* GetTransform()const {return mTransform; }
	float GetXMin() const { return mTransform->GetPosition().x - (mWidth / 2); }
	float GetXMax() const { return mTransform->GetPosition().x + (mWidth / 2); }
	float GetYMin() const { return mTransform->GetPosition().y - (mHeight / 2); }
	float GetYMax() const { return mTransform->GetPosition().y + (mHeight / 2); }
	float GetZMin() const { return mTransform->GetPosition().z - (mDepth / 2); }
	float GetZMax() const { return mTransform->GetPosition().z + (mWidth / 2); }

private:
	Transform* mTransform;
	float mHeight, mWidth, mDepth;
};

class Plane {

};
#endif // !_COLLIDER_H

