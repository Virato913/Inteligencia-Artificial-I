#include "Vector.h"

Vector::Vector()
{
	x = 0;
	y = 0;
}

Vector::Vector(float a, float b)
{
	x = a;
	y = b;
}

Vector Vector::normalized()
{
	Vector pivot = *this;
	pivot.normalize();
	return pivot;
}

void Vector::normalize()
{
	*this = *this / this->lenght();
}

float Vector::lenght()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float Vector::angle()
{
	return atan2(y, x) * 180 / PI;
}

float Vector::dot(Vector b)
{
	return (x*b.x + y*b.y);
}

Vector Vector::projection(Vector b)
{
	return b * (dot(b) / pow(lenght(), 2));
}

Vector Vector::cross()
{
	return Vector(y, -x);
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