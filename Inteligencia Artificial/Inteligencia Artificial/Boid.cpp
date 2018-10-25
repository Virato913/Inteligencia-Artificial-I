#include "Boid.h"

CBoid::CBoid()
{
	m_dir = Vector(0, 0);
}

CBoid::~CBoid()
{
	
}

Vector CBoid::getDir()
{
	return m_dir;
}

void CBoid::setDir(Vector dir)
{
	m_dir = dir;
}

Vector CBoid::seek(Vector pos, float mag)
{
	Vector seekForce = pos - getPos();
	seekForce.normalize();
	return seekForce * mag;
}

Vector CBoid::flee(Vector pos, float mag, float radius)
{
	Vector fleeForce = getPos() - pos;
	if (radius != 0)
	{
		if (fleeForce.lenght() < radius)
			fleeForce.normalize();
		else
			fleeForce *= 0;
	}
	else
		fleeForce.normalize();
	return fleeForce * mag;
}

Vector CBoid::pursue(CBoid other, float time, float mag)
{
	Vector pursueForce = seek(getDir()*time, mag);
	pursueForce.normalize();
	return pursueForce * mag;
}

Vector CBoid::evade(CBoid other, float time, float mag)
{
	Vector evadeForce = flee(other.getDir()*time, mag) + flee(other.getPos(), mag);
	evadeForce.normalize();
	return evadeForce * mag;
}

Vector CBoid::wanderRandom(float mag)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<> distr(-1, 1);
	Vector pivot(distr(eng), distr(eng));
	pivot.normalize();
	return pivot * mag;
}

Vector CBoid::wanderDir(float dist, float radius, float angle, float mag)
{
	//Get the point for the circle center
	Vector circleCenter = m_dir.normalized() * dist;
	//Get the point for the cicle
	Vector circle = circleCenter.normalized() * (dist + radius);
	//Declare the random point
	Vector randomPoint = circle - circleCenter;
	//Get a random angle within the circle
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<> distr(m_dir.angle() - (angle / 2), m_dir.angle + (angle / 2));
	Vector pivot(distr(eng), distr(eng));
}

Vector CBoid::followPath(Vector pos, float mag)
{

}

Vector CBoid::patrol(Vector pos, float mag)
{

}