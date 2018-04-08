#pragma once
#include <float.h>
#include <SDL.h> //for numerical value of PI
#include "Vector.h"

class Quaternion
{
public:
	float r;
	float i;
	float j;
	float k;

	Quaternion() : r(1), i(0), j(0), k(0) {}
	Quaternion(const float r, const float i, const float j, const float k) : r(r), i(i), j(j), k(k) {}
	Quaternion(const Quaternion& q) : r(q.r), i(q.i), j(q.j), k(q.k) {}
	~Quaternion() {};

	void normalise()
	{
		float d = r*r + i*i + j*j + k*k;

		if (d < FLT_EPSILON)
		{
			r = 1;
		}
		else
		{
			d = static_cast<float>(1.0) / sqrtf(d);
			r *= d;
			i *= d;
			j *= d;
			k *= d;
		}
	}

	
	Quaternion operator* (const Quaternion &multiplier)
	{
		Quaternion q;
		q.r = r*multiplier.r - i*multiplier.i - j*multiplier.j - k*multiplier.k;
		q.i = r*multiplier.i + i*multiplier.r + j*multiplier.k - k*multiplier.j;
		q.j = r*multiplier.j + j*multiplier.r + k*multiplier.i - i*multiplier.k;
		q.k = r*multiplier.k + k*multiplier.r + i*multiplier.j - j*multiplier.i;
		return q;
	}

	void RotateByVector(const Vector3D& vector)
	{
		Quaternion q(0, vector.x, vector.y, vector.z);
		*this = *this * q;
	}

	void AddScaledVector(const Vector3D& vector, float scale)
	{
		Quaternion q(0, vector.x * scale, vector.y * scale, vector.z * scale);

		q = *this * q;
		r += q.r * 0.5f;
		i += q.i * 0.5f;
		j += q.j * 0.5f;
		k += q.k * 0.5f;
	}

	static void CreateAxisAngleRotationMatrix(const Quaternion quaternion, float& angle, Vector3D& axis)
	{
		Quaternion q = quaternion;
		if (q.r > 1)
			q.normalise();
		angle = 2 * acos(q.r);
		double s = sqrtf(1 - q.r*q.r);

		if (s < 0.001)
		{
			axis.x = q.i;
			axis.y = q.j;
			axis.z = q.k;
		}
		else
		{
			axis.x = q.i / s;
			axis.y = q.j / s;
			axis.z = q.k / s;
		}

		//convert to degrees
		angle *= (180 / M_PI);
	}
};
