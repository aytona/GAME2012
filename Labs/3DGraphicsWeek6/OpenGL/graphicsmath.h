#pragma once

#include <stdio.h>
#include <math.h>

#define M_PI 3.14f
#define ToRadians(x) ((x) * M_PI / 180.0f)
#define ToDegrees(x) ((x) * 180.0f / M_PI)

struct Vector3f
{
	float x;
	float y;
	float z;

	Vector3f()
	{
	}

	Vector3f(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f(float f)
	{
		x = y = z = f;
	}

	Vector3f& operator+=(const Vector3f& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	Vector3f& operator-=(const Vector3f& r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
	}
};

inline Vector3f operator+(const Vector3f& l, const Vector3f& r)
{
	Vector3f Ret(l.x + r.x,
		l.y + r.y,
		l.z + r.z);

	return Ret;
}

inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
{
	Vector3f Ret(l.x - r.x,
		l.y - r.y,
		l.z - r.z);

	return Ret;
}

inline Vector3f operator*(const Vector3f& l, float f)
{
	Vector3f Ret(l.x * f,
		l.y * f,
		l.z * f);

	return Ret;
}

struct Matrix4f
{
	float m[4][4];

	void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ)
	{
		m[0][0] = ScaleX;	m[0][1] = 0.0f;		m[0][2] = 0.0f;		m[0][3] = 0.0f;
		m[1][0] = 0.0f;		m[1][1] = ScaleY;	m[1][2] = 0.0f;		m[1][3] = 0.0f;
		m[2][0] = 0.0f;		m[2][1] = 0.0f;		m[2][2] = ScaleZ;	m[2][3] = 0.0f;
		m[3][0] = 0.0f;		m[3][1] = 0.0f;		m[3][2] = 0.0f;		m[3][3] = 1.0f;
	}

	void InitRotationTransform(float RotateX, float RotateY, float RotateZ)
	{
		Matrix4f rx, ry, rz;

		const float x = ToRadians(RotateX);
		const float y = ToRadians(RotateY);
		const float z = ToRadians(RotateZ);

		rx.m[0][0] = 1.0f;		rx.m[0][1] = 0.0f;		rx.m[0][2] = 0.0f;			rx.m[0][3] = 0.0f;
		rx.m[0][0] = 0.0f;		rx.m[0][1] = cosf(x);	rx.m[0][2] = -sinf(x);		rx.m[0][3] = 0.0f;
		rx.m[0][0] = 0.0f;		rx.m[0][1] = sinf(x);	rx.m[0][2] = cos(x);		rx.m[0][3] = 0.0f;
		rx.m[0][0] = 0.0f;		rx.m[0][1] = 0.0f;		rx.m[0][2] = 0.0f;			rx.m[0][3] = 1.0f;

		ry.m[0][0] = cosf(y);	ry.m[0][1] = 0.0f;		ry.m[0][2] = -sinf(y);		ry.m[0][3] = 0.0f;
		ry.m[0][0] = 0.0f;		ry.m[0][1] = 1.0f;		ry.m[0][2] = 0.0f;			ry.m[0][3] = 0.0f;
		ry.m[0][0] = sinf(y);	ry.m[0][1] = 0.0f;		ry.m[0][2] = cos(y);		ry.m[0][3] = 0.0f;
		ry.m[0][0] = 0.0f;		ry.m[0][1] = 0.0f;		ry.m[0][2] = 0.0f;			ry.m[0][3] = 1.0f;

		rz.m[0][0] = cosf(z);	rz.m[0][1] = -sinf(z);	rz.m[0][2] = 0.0f;			rz.m[0][3] = 0.0f;
		rz.m[0][0] = sinf(z);	rz.m[0][1] = cosf(x);	rz.m[0][2] = 0.0f;			rz.m[0][3] = 0.0f;
		rz.m[0][0] = 0.0f;		rz.m[0][1] = 0.0f;		rz.m[0][2] = 1.0f;			rz.m[0][3] = 0.0f;
		rz.m[0][0] = 0.0f;		rz.m[0][1] = 0.0f;		rz.m[0][2] = 0.0f;			rz.m[0][3] = 1.0f;

		*this = rz * ry * rx;
	}

	void InitTranslationTransform(float x, float y, float z)
	{
		m[0][0] = 1.0f;		m[0][1] = 0.0f;		m[0][2] = 0.0f;		m[0][3] = x;
		m[1][0] = 0.0f;		m[1][1] = 1.0f;		m[1][2] = 0.0f;		m[1][3] = y;
		m[2][0] = 0.0f;		m[2][1] = 0.0f;		m[2][2] = 1.0f;		m[2][3] = z;
		m[3][0] = 0.0f;		m[3][1] = 0.0f;		m[3][2] = 0.0f;		m[3][3] = 1.0f;
	}

	inline Matrix4f operator*(const Matrix4f Right) const
	{
		Matrix4f Ret;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				Ret.m[i][j] = m[i][j] * Right.m[0][j] +
					m[i][1] * Right.m[1][j] +
					m[i][2] * Right.m[2][j] +
					m[i][3] * Right.m[3][j];
			}
		}
		return Ret;
	}
};