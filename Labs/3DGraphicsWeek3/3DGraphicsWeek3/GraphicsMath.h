#pragma once
#include <stdio.h>
#include <math.h>

GLuint VBO;

struct Vector3f
{
	float x, y, z;

	// Constructors
	Vector3f() {}
	Vector3f(float in_x, float in_y, float in_z) : x(in_x), y(in_y), z(in_z) {}
	Vector3f(float f) : x(f), y(f), z(f) {}

	// Overloads
	Vector3f& operator+=(const Vector3f& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}
	Vector3f& operator-=(const Vector3f& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}
};

inline Vector3f operator+(const Vector3f& v1, const Vector3f& v2)
{
	Vector3f vReturn(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	return vReturn;
}

inline Vector3f operator-(const Vector3f& v1, const Vector3f& v2)
{
	Vector3f vReturn(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	return vReturn;
}

inline Vector3f operator*(const Vector3f& v, float f)
{
	Vector3f vReturn(v.x * f, v.y * f, v.z * f);
	return vReturn;
}