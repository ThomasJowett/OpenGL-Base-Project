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

#endif // !_COLLIDER_H

