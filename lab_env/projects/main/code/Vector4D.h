#pragma once
#include <cmath>

//!  A Vector 4D Class 
/*!
  A Vector 4D class supporting:
	� Addition, subtraction, scaling (multiply with a scalar), length, normalize, dot product, cross product
*/

class Vector4D
{
public:
	/// Empty constructor makes the vector (0, 0, 0, 1)
	Vector4D();
	/// Constructor recieving x-y-z values and defaults w-value to 1
	Vector4D(const float & x, const float & y, const float & z);
	/// Constructor recieving x-y-z and w values
	Vector4D(const float & x, const float & y, const float & z, const float & w);
	/// Constructor recieving array with x-y-z and w values
	Vector4D(const float* xyzw);
	
	/// Get using []
	float operator[](const int & i) const;
	/// Set using []
	float & operator[](const int & i);

	float * getFloatPointer();
	/// Vector addition
	Vector4D operator+(const Vector4D & v2);
	/// Vector subtraction
	Vector4D operator-(const Vector4D & v2);
	/// Vector dot product
	float operator*(const Vector4D & v2);
	/// Vector multiplied witch scalar
	Vector4D operator*(const float & a);
	/// == operator modified to work with vectors
	bool operator==(const Vector4D & v2);
	/// != operator modified to work with vectors
	bool operator!=(const Vector4D & v2);
	/// Calculates the length of the vector
	float length() const;
	/// Returns this vetor normalized
	Vector4D norm() const;
	/// Cross product between two vectors
	Vector4D cross(const Vector4D & v2);
	
	// Lerp between two vectors
	static Vector4D lerp(const Vector4D & v1, const Vector4D & v2, float amount);
	// Lerp between two quaternions
	static Vector4D slerp(Vector4D & v1, Vector4D & v2, float amount);

private:
	/// Array of floats used to save values in vector
	float v[4];
};

inline Vector4D::Vector4D()
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = 1.0f;
}

inline Vector4D::Vector4D(const float & x, const float & y, const float & z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = 1.0f;
};

inline Vector4D::Vector4D(const float & x, const float & y, const float & z, const float & w)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
};

inline Vector4D::Vector4D(const float* xyzw)
{
	v[0] = xyzw[0],
	v[1] = xyzw[1],
	v[2] = xyzw[2],
	v[3] = xyzw[3];
};

inline float Vector4D::operator[](const int & i) const //Get
{
	return v[i];
}

inline float & Vector4D::operator[](const int & i) //Set
{
	return v[i];
}

inline float * Vector4D::getFloatPointer()
{
	return v;
}

inline Vector4D Vector4D::operator+(const Vector4D & v2)
{
	return Vector4D(
		v[0] + v2[0],
		v[1] + v2[1],
		v[2] + v2[2],
		v[3] + v2[3]);
}

inline Vector4D Vector4D::operator-(const Vector4D & v2)
{
	return Vector4D(
		v[0] - v2[0],
		v[1] - v2[1],
		v[2] - v2[2],
		v[3] - v2[3]);
}

inline float Vector4D::operator*(const Vector4D & v2)
{
	return 
		v[0] * v2[0] +
		v[1] * v2[1] + 
		v[2] * v2[2] +
		v[3] * v2[3];
}

inline Vector4D Vector4D::operator*(const float & a)
{
	return Vector4D(
		v[0] * a,
		v[1] * a,
		v[2] * a,
		v[3] * a);
}

inline bool Vector4D::operator==(const Vector4D & v2)
{
	return 
		v[0] == v2[0] &&
		v[1] == v2[1] && 
		v[2] == v2[2] &&
		v[3] == v2[3];
}

inline bool Vector4D::operator!=(const Vector4D & v2)
{
	return
		v[0] != v2[0] ||
		v[1] != v2[1] ||
		v[2] != v2[2] ||
		v[3] != v2[3];
}

inline float Vector4D::length() const
{
	return sqrt(
		v[0] * v[0] + 
		v[1] * v[1] + 
		v[2] * v[2]);
}

inline Vector4D Vector4D::norm() const
{
	float l = this->length();
	return Vector4D(
		v[0] / l,
		v[1] / l,
		v[2] / l,
		1);
}

inline Vector4D Vector4D::cross(const Vector4D & v2)
{
	return Vector4D(
		v[1] * v2[2] - v[2] * v2[1], 
		v[2] * v2[0] - v[0] * v2[2], 
		v[0] * v2[1] - v[1] * v2[0], 
		1.0f);
}

inline Vector4D Vector4D::lerp(const Vector4D & v1, const Vector4D & v2, float amount)
{
	return Vector4D(
		v1[0] * (1 - amount) + v2[0] * amount,
		v1[1] * (1 - amount) + v2[1] * amount,
		v1[2] * (1 - amount) + v2[2] * amount,
		v1[3] * (1 - amount) + v2[3] * amount);
}
	
inline Vector4D Vector4D::slerp(Vector4D & v1, Vector4D & v2, float amount)
{
	float cosVal = v1*v2;
	if (cosVal < 0)
	{
		v2 = v2 * -1;
		cosVal = -cosVal;
	}

	if (cosVal > 0.9999f)
	{
		return Vector4D::lerp(v1, v2, amount);
	}
	

	float angle = acosf(cosVal);
	float newAngle = angle * amount;

	float f1 = cosf(newAngle) - cosVal * sinf(newAngle) / sinf(angle);
	float f2 = sinf(newAngle) / sinf(angle);

	return Vector4D((v1 * f1) + (v2 * f2));
}
