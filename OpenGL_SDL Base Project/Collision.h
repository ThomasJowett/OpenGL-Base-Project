#ifndef _COLLISION_H
#define _COLLISION_H

#include "Vector.h"

class Sphere {
public:
	Sphere(Vector3D centre, float radius) : mCentre(centre), mRadius(radius) { mCollided = false; }
	float GetBoundingRadius() const { return mRadius; }
	Vector3D GetCentre() { return mCentre; }
	void Update(Vector3D newPosition) { mCentre = newPosition; }
	void SetCollided(bool collided) { mCollided = collided; }
	bool GetCollided() const { return mCollided; }

private:
	Vector3D mCentre;
	float mRadius;
	bool mCollided;
};

class Collision {
public:
	static bool SphereSphereCollision(Sphere * sphere1, Sphere * sphere2) {
		Vector3D centre1 = sphere1->GetCentre();
		Vector3D centre2 = sphere2->GetCentre();
		
		Vector3D distance = centre2 - centre1;

		float sumOfBoundingRadii = sphere1->GetBoundingRadius() + sphere2->GetBoundingRadius();
		if (distance.GetSqrMagnitude() < (sumOfBoundingRadii * sumOfBoundingRadii)) {
			sphere1->SetCollided(true);
			sphere2->SetCollided(true);
			return true;
		}
		return false;
	}
};

#endif // !_COLLISION_H
