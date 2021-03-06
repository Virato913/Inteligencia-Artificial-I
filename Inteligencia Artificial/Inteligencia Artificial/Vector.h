#pragma once

#include <math.h>

#define PI atan(1)*4

struct Vector
{
	float x, y;
	Vector();
	Vector(float _x, float _y);
	Vector normalized();
	void normalize();
	float length();
	float angle();
	float dot(Vector b);
	Vector projection(Vector b);
	Vector cross();
	Vector truncate(float maxMag);

	Vector operator+(Vector other);
	void operator+=(Vector other);
	Vector operator-(Vector other);
	void operator-=(Vector other);
	Vector operator*(float times);
	void operator*=(float times);
	Vector operator/(float times);
	void operator/=(float times);
	void operator=(Vector other);
	bool operator==(Vector other);
	bool operator!=(Vector other);
};
