#pragma once
#include "Vector4D.h"

//!  A Matrix 4D Class 
/*!
  A Matrix 4D class supporting:
	� Product, product with vector
	� Initialization functions for rotation matrices around the x,y,z axis and an arbitrary vector.
	� Transpose and inverse
	� Creating identity and translation matrixes
*/

class Matrix4D
{
public:
	/// Empty constructor creates identity matrix
	Matrix4D();
	/// Constructor copying already existing matrix
	Matrix4D(const Matrix4D & m2);
	/// Constructor using array of floats
	Matrix4D(const float f[16]);
	/// Constructor using 16 floats sent in separately
	Matrix4D(
		const float & a1, const float & b1, const float & c1, const float & d1, 
		const float & a2, const float & b2, const float & c2, const float & d2, 
		const float & a3, const float & b3, const float & c3, const float & d3, 
		const float & a4, const float & b4, const float & c4, const float & d4);
	/// Matrix * Matrix multiplication
	Matrix4D operator*(const Matrix4D & m2);
	/// Matrix * Vector multiplication
	Vector4D operator*(const Vector4D & v);
	/// Get using (row, column)
	float operator()(const int & row, const int & column) const;
	/// Set using (row, column)
	float & operator()(const int & row, const int & column);
	/// Get float pointer to all elements
	float* getFloatPointer();
	/// Return transpose of current matrix
	Matrix4D transpose() const;
	/// Return inverse of current matrix
	Matrix4D inverse() const;
	 
	/// Get rotation matrix around x axis
	static Matrix4D getRotationMatrixX(const float & rad);
	/// Get rotation matrix around y axis
	static Matrix4D getRotationMatrixY(const float & rad);
	/// Get rotation matrix around z axis
	static Matrix4D getRotationMatrixZ(const float & rad);
	/// Get rotation matrix around arbitrary axis. Arbitrary axis represented by normalized vector v
	static Matrix4D getRotationMatrixVector(const float & rad, const Vector4D & v);
	/// Get rotation matrix from quaternion
	static Matrix4D getRotationMatrixQuaternion(Vector4D quat);
	/// Get identity matrix
	static Matrix4D getIdentityMatrix();
	/// Get scale matrix
	static Matrix4D getScaleMatrix(Vector4D v);
	/// Get a translation matrix using a vector
	static Matrix4D getTranslationMatrix(Vector4D v);

	static Matrix4D getPerspectiveMatrix(float l, float r, float t, float b, float f, float n);

	static Matrix4D lookAt(Vector4D cameraPos, Vector4D targetPos, Vector4D upVector);
private:
	/// Array of floats used to save values in matrix
	float m[16];
};

inline Matrix4D::Matrix4D()
{
	Matrix4D im = getIdentityMatrix();
	m[0] = im.m[0];		m[1] = im.m[1];		m[2] = im.m[2];		m[3] = im.m[3];
	m[4] = im.m[4];		m[5] = im.m[5];		m[6] = im.m[6];		m[7] = im.m[7];
	m[8] = im.m[8];		m[9] = im.m[9];		m[10] = im.m[10];	m[11] = im.m[11];
	m[12] = im.m[12];	m[13] = im.m[13];	m[14] = im.m[14];	m[15] = im.m[15];
}

inline Matrix4D::Matrix4D(const Matrix4D & m2)
{
	m[0] = m2.m[0];		m[1] = m2.m[1];		m[2] = m2.m[2];		m[3] = m2.m[3]; 
	m[4] = m2.m[4];		m[5] = m2.m[5];		m[6] = m2.m[6];		m[7] = m2.m[7]; 
	m[8] = m2.m[8];		m[9] = m2.m[9];		m[10] = m2.m[10];	m[11] = m2.m[11]; 
	m[12] = m2.m[12];	m[13] = m2.m[13];	m[14] = m2.m[14];	m[15] = m2.m[15];
}

inline Matrix4D::Matrix4D(const float f[16])
{
	m[0] = f[0];	m[1] = f[1];	m[2] = f[2];	m[3] = f[3];
	m[4] = f[4];	m[5] = f[5];	m[6] = f[6];	m[7] = f[7];
	m[8] = f[8];	m[9] = f[9];	m[10] = f[10];	m[11] = f[11];
	m[12] = f[12];	m[13] = f[13];	m[14] = f[14];	m[15] = f[15];
}

inline Matrix4D::Matrix4D(
		const float & a1, const float & b1, const float & c1, const float & d1,
		const float & a2, const float & b2, const float & c2, const float & d2,
		const float & a3, const float & b3, const float & c3, const float & d3,
		const float & a4, const float & b4, const float & c4, const float & d4)
{
	m[0] = a1;		m[1] = b1;		m[2] = c1;		m[3] = d1;
	m[4] = a2;		m[5] = b2;		m[6] = c2;		m[7] = d2;
	m[8] = a3;		m[9] = b3;		m[10] = c3;		m[11] = d3;
	m[12] = a4;		m[13] = b4;		m[14] = c4;		m[15] = d4;
}

inline Matrix4D Matrix4D::operator*(const Matrix4D & m2)
{
	return Matrix4D(
		m[0] * m2.m[0] + m[1] * m2.m[4] + m[2] * m2.m[8] + m[3] * m2.m[12],
		m[0] * m2.m[1] + m[1] * m2.m[5] + m[2] * m2.m[9] + m[3] * m2.m[13],
		m[0] * m2.m[2] + m[1] * m2.m[6] + m[2] * m2.m[10] + m[3] * m2.m[14],
		m[0] * m2.m[3] + m[1] * m2.m[7] + m[2] * m2.m[11] + m[3] * m2.m[15],

		m[4] * m2.m[0] + m[5] * m2.m[4] + m[6] * m2.m[8] + m[7] * m2.m[12],
		m[4] * m2.m[1] + m[5] * m2.m[5] + m[6] * m2.m[9] + m[7] * m2.m[13],
		m[4] * m2.m[2] + m[5] * m2.m[6] + m[6] * m2.m[10] + m[7] * m2.m[14],
		m[4] * m2.m[3] + m[5] * m2.m[7] + m[6] * m2.m[11] + m[7] * m2.m[15],

		m[8] * m2.m[0] + m[9] * m2.m[4] + m[10] * m2.m[8] + m[11] * m2.m[12],
		m[8] * m2.m[1] + m[9] * m2.m[5] + m[10] * m2.m[9] + m[11] * m2.m[13],
		m[8] * m2.m[2] + m[9] * m2.m[6] + m[10] * m2.m[10] + m[11] * m2.m[14],
		m[8] * m2.m[3] + m[9] * m2.m[7] + m[10] * m2.m[11] + m[11] * m2.m[15],

		m[12] * m2.m[0] + m[13] * m2.m[4] + m[14] * m2.m[8] + m[15] * m2.m[12],
		m[12] * m2.m[1] + m[13] * m2.m[5] + m[14] * m2.m[9] + m[15] * m2.m[13],
		m[12] * m2.m[2] + m[13] * m2.m[6] + m[14] * m2.m[10] + m[15] * m2.m[14],
		m[12] * m2.m[3] + m[13] * m2.m[7] + m[14] * m2.m[11] + m[15] * m2.m[15]);
}

inline Vector4D Matrix4D::operator*(const Vector4D & v)
{
	return Vector4D(
		m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3] * v[3], 
		m[4] * v[0] + m[5] * v[1] + m[6] * v[2] + m[7] * v[3], 
		m[8] * v[0] + m[9] * v[1] + m[10] * v[2] + m[11] * v[3], 
		m[12] * v[0] + m[13] * v[1] + m[14] * v[2] + m[15] * v[3]);
}

inline float Matrix4D::operator()(const int & row, const int & column) const //Get
{
	return m[row * 4 + column];
}

inline float & Matrix4D::operator()(const int & row, const int & column) //Set
{
	return m[row * 4 + column];
}

inline float * Matrix4D::getFloatPointer()
{
	return m;
}

inline Matrix4D Matrix4D::transpose() const
{
	float tempMatrix[16] = { 
		m[0],		m[1],		m[2],		m[3],
		m[4],		m[5],		m[6],		m[7],
		m[8],		m[9],		m[10],		m[11],
		m[12],		m[13],		m[14],		m[15] };

	tempMatrix[4] = m[1];	tempMatrix[1] = m[4];
	tempMatrix[8] = m[2];	tempMatrix[2] = m[8];
	tempMatrix[12] = m[3];	tempMatrix[3] = m[12];
	tempMatrix[9] = m[6];	tempMatrix[6] = m[9];
	tempMatrix[13] = m[7];	tempMatrix[7] = m[13];
	tempMatrix[14] = m[11];	tempMatrix[11] = m[14];
	return tempMatrix;
}

inline Matrix4D Matrix4D::inverse() const
{
	float tempMatrix[16];

	tempMatrix[0] = 
		m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	tempMatrix[4] = 
		-m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	tempMatrix[8] = 
		m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	tempMatrix[12] = 
		-m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	tempMatrix[1] = 
		-m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	tempMatrix[5] = 
		m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	tempMatrix[9] = 
		-m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	tempMatrix[13] = 
		m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	tempMatrix[2] = 
		m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	tempMatrix[6] = 
		-m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	tempMatrix[10] =
		m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	tempMatrix[14] = 
		-m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	tempMatrix[3] = 
		-m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	tempMatrix[7] = 
		m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	tempMatrix[11] = 
		-m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	tempMatrix[15] = 
		m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	float det;
	det = m[0] * tempMatrix[0] + m[1] * tempMatrix[4] + m[2] * tempMatrix[8] + m[3] * tempMatrix[12];

	if (det == 0.0f) {
		throw "Determinant was 0";
		return Matrix4D();
	}


	det = 1.0f / det;

	for (int i = 0; i < 16; i++) 
	{
		tempMatrix[i] = tempMatrix[i] * det;
	}
	return Matrix4D(tempMatrix);
}

inline Matrix4D Matrix4D::getRotationMatrixX(const float & rad)
{
	float s = sinf(rad);
	float c = cosf(rad);
	return Matrix4D(
		1.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, c,	-s,	  0.0f, 
		0.0f, s,	c,	  0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4D Matrix4D::getRotationMatrixY(const float & rad)
{
	float s = sinf(rad);
	float c = cosf(rad);
	return Matrix4D(
		c,	  0.0f, s,	  0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-s,	  0.0f, c,	  0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4D Matrix4D::getRotationMatrixZ(const float & rad)
{
	float s = sinf(rad);
	float c = cosf(rad);
	return Matrix4D(
		c,	  -s,	0.0f, 0.0f,
		s,	  c,	0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4D Matrix4D::getRotationMatrixVector(const float & rad, const Vector4D & v)
{
	float s = sinf(rad);
	float c = cosf(rad);
	return Matrix4D(
		c + v[0] * v[0] * (1 - c),			v[0] * v[1] * (1 - c) - v[2] * s,	v[0] * v[2] * (1 - c) + v[1] * s,	0.0f,
		v[1] * v[0] * (1 - c) + v[2] * s,	c + v[1] * v[1] * (1 - c), 			v[1] * v[2] * (1 - c) - v[0] * s,	0.0f,
		v[2] * v[0] * (1 - c) - v[1] * s,	v[2] * v[1] * (1 - c) + v[0] * s,	c + v[2] * v[2] * (1 - c),			0.0f,
		0.0f,								0.0f,								0.0f,								1.0f);
}

inline Matrix4D Matrix4D::getRotationMatrixQuaternion(Vector4D quat)
{
    float n = 1.0f/sqrt(quat[0]*quat[0]+quat[1]*quat[1]+quat[2]*quat[2]+quat[3]*quat[3]);
    quat[0] *= n;
    quat[1] *= n;
    quat[2] *= n;
    quat[3] *= n;
    return Matrix4D(
    1 - 2*quat[1]*quat[1] - 2*quat[2]*quat[2], 	2*quat[0]*quat[1] - 2*quat[2]*quat[3], 		2*quat[0]*quat[2] + 2*quat[1]*quat[3], 		0,
    2*quat[0]*quat[1] + 2*quat[2]*quat[3], 		1 - 2*quat[0]*quat[0] - 2*quat[2]*quat[2], 	2*quat[1]*quat[2] - 2*quat[0]*quat[3], 		0,
    2*quat[0]*quat[2] - 2*quat[1]*quat[3], 		2*quat[1]*quat[2] + 2*quat[0]*quat[3], 		1 - 2*quat[0]*quat[0] - 2*quat[1]*quat[1], 	0,
    0, 											0, 											0, 											1);
}

inline Matrix4D Matrix4D::getIdentityMatrix()
{
	return Matrix4D(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4D Matrix4D::getScaleMatrix(Vector4D v)
{
	return Matrix4D(
		v[0], 0.0f, 0.0f, 0.0f,
		0.0f, v[1], 0.0f, 0.0f,
		0.0f, 0.0f, v[2], 0.0f,
		0.0f, 0.0f, 0.0f, 1);
}

inline Matrix4D Matrix4D::getTranslationMatrix(Vector4D v)
{
	return Matrix4D(
		1.0f, 0.0f, 0.0f, v[0],
		0.0f, 1.0f, 0.0f, v[1],
		0.0f, 0.0f, 1.0f, v[2],
		0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4D Matrix4D::getPerspectiveMatrix(float l, float r, float t, float b, float f, float n)
{
	return Matrix4D(
		(2 * n) / (r - l), 0, (r + l) / (r - l), 0,
		0, (2 * n) / (t - b), (t + b) / (t - b), 0,
		0, 0, -(f + n) / (f - n), -(2 * f * n) / (f - n),
		0, 0, -1, 0
	);
}

inline Matrix4D Matrix4D::lookAt(Vector4D cameraPos, Vector4D targetPos, Vector4D upVector)
{
	Vector4D cameraDir = (cameraPos - targetPos).norm();
	Vector4D rightAxis = (upVector.norm().cross(cameraDir)).norm();
	Vector4D upAxis = cameraDir.cross(rightAxis);
	return Matrix4D
	(
		rightAxis[0],	rightAxis[1],	rightAxis[2],	0,
		upAxis[0],		upAxis[1],		upAxis[2],		0,
		cameraDir[0],	cameraDir[1],	cameraDir[2],	0,
		0,				0,				0,				1
	) * Matrix4D::getTranslationMatrix(Vector4D(-targetPos[0], -targetPos[1], -targetPos[2]));
}