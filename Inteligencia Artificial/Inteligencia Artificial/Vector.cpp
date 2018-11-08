#include "Vector.h"

Vector::Vector()
{
	x = 0;
	y = 0;
}

Vector::Vector(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector Vector::normalized()
{
	Vector pivot = *this;
	pivot.normalize();
	return pivot;
}

void Vector::normalize()
{
	*this = *this / this->length();
}

float Vector::length()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float Vector::angle()
{
	float ret = 0;
	if (x == 0)
		if (y == 0)
			return ret = 0;
		else
			if (y > 0)
				return ret = 90;
			else
				return ret = 270;
	else
		if (y == 0)
			if (x > 0)
				return ret = 0;
			else
				if (x < 0)
					return ret = 180;
	ret = atanf(y / x) * (180 / PI);
	ret /= 16;
	if (x < 0 && y < 0)
		ret += 180;
	else
		if (x < 0)
			ret += 180;
		else
			if (y < 0)
				ret += 360;
	return ret;
}

float Vector::dot(Vector b)
{
	return (x*b.x + y*b.y);
}

Vector Vector::projection(Vector b)
{
	return b * (dot(b) / pow(length(), 2));
}

Vector Vector::cross()
{
	return Vector(y, -x);
}

Vector Vector::truncate(float maxMag)
{
	float mag = length();
	if (mag > maxMag)
	{
		normalize();
		*this *= maxMag;
	}
	return *this;
}

Vector Vector::operator+(Vector other)
{
	Vector pivot = *this;
	pivot += other;
	return pivot;
}

void Vector::operator+=(Vector other)
{
	x += other.x;
	y += other.y;
}

Vector Vector::operator-(Vector other)
{
	Vector pivot = *this;
	pivot -= other;
	return pivot;
}

void Vector::operator-=(Vector other)
{
	x -= other.x;
	y -= other.y;
}

Vector Vector::operator*(float times)
{
	Vector pivot = *this;
	pivot *= times;
	return pivot;
}

void Vector::operator*=(float times)
{
	x *= times;
	y *= times;
}

Vector Vector::operator/(float times)
{
	Vector pivot = *this;
	pivot /= times;
	return pivot;
}

void Vector::operator/=(float times)
{
	x /= times;
	y /= times;
}

void Vector::operator=(Vector other)
{
	x = other.x;
	y = other.y;
}

bool Vector::operator==(Vector other)
{
	return (x == other.x && y == other.y);
}

bool Vector::operator!=(Vector other)
{
	return !(*this == other);
}
