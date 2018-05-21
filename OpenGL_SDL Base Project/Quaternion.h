#pragma once
#include <float.h>
#include <SDL.h> //for numerical value of PI
#include "Vector.h"

class Quaternion
{
public:
	float r;	//Real
	float i;	//First Complex
	float j;	//Second Complex
	float k;	//Thrid Complex

	Quaternion() : r(1), i(0), j(0), k(0) {}
	Quaternion(const float r, const float i, const float j, const float k) : r(r), i(i), j(j), k(k) {}
	Quaternion(const Quaternion& q) : r(q.r), i(q.i), j(q.j), k(q.k) {}

	//from a vector of 3 euler angles in radians
	Quaternion(const Vector3D angles)
	{
		float cos_x_2 = cosf(0.5f*angles.x);
		float cos_y_2 = cosf(0.5f*angles.y);
		float cos_z_2 = cosf(0.5f*angles.z);

		float sin_x_2 = sinf(0.5f*angles.x);
		float sin_y_2 = sinf(0.5f*angles.y);
		float sin_z_2 = sinf(0.5f*angles.z);

		// and now compute quaternion
		r = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
		i = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
		j = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
		k = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
	}

	//from 3 euler angles in radians
	Quaternion(const float theta_Roll, float theta_Pitch, float theta_Yaw)
	{
		(*this) = Quaternion(Vector3D(theta_Roll, theta_Pitch, theta_Yaw));
	}

	~Quaternion() {};

	float GetSqrMagnitude()
	{
		return r*r + i*i + j*j + k*k;
	}

	float GetMagnitude()
	{
		return sqrtf(GetSqrMagnitude());
	}

	void Normalize()
	{
		float d = GetSqrMagnitude();

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

	Quaternion Conjugate()
	{
		return Quaternion(r, -i, -j, -k);
	}

	Quaternion Scale(float scaler)
	{
		return Quaternion(r*scaler, i*scaler, j*scaler, k*scaler);
	}

	Quaternion Inverse()
	{
		return Conjugate().Scale(1 / GetSqrMagnitude());
	}

	Quaternion UnitQuaternion()
	{
		return (*this).Scale(1 / (*this).GetMagnitude());
	}

	//Operators---------------------------------------------------------------------------------
	const Quaternion &operator +=(const Quaternion &q)
	{
		r += q.r;
		i += q.i;
		j += q.j;
		k += q.k;
		return *this;
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

	Vector3D operator*(const Vector3D& multiplier)
	{
		Vector3D V = multiplier;
		return RotateVectorByQuaternion(V);
	}

	void RotateByVector(const Vector3D& vector)
	{
		Quaternion q(0, vector.x, vector.y, vector.z);
		*this = *this * q;
	}

	Vector3D RotateVectorByQuaternion(Vector3D& vector)
	{
		Quaternion V(0, vector.x, vector.y, vector.z);
		V = (*this * V * this->Conjugate());
		vector.x = V.i;
		vector.z = V.j;
		vector.z = V.k;
		return vector;
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

	static void CreateAxisAngleRotation(const Quaternion quaternion, float& angle, Vector3D& axis)
	{
		Quaternion q = quaternion;
		if (q.r > 1)
			q.Normalize();
		angle = 2 * (float)acos(q.r);
		float s = sqrtf(1 - q.r*q.r);

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
		angle *= (float)(180 / M_PI);
	}
};
