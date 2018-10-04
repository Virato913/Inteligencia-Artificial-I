#include "Boid.h"

CBoid::CBoid()
{

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
	return seekForce*mag;
}

Vector CBoid::flee(Vector pos, float mag)
{
	Vector fleeForce = getPos() - pos;
	fleeForce.normalize();
	return fleeForce*mag;
}

Vector CBoid::pursue(CBoid other, float time, float mag)
{
	Vector pursueForce = seek(getDir()*time, mag);
	pursueForce.normalize();
	return pursueForce*mag;
}

Vector CBoid::evade(CBoid other, float time, float mag)
{
	Vector evadeForce = flee(other.getDir()*time, mag) + flee(other.getPos(), mag);
	evadeForce.normalize();
	return evadeForce*mag;
}

Vector CBoid::wanderRandom(float mag)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<> distr(-1, 1);
	Vector pivot(distr(eng), distr(eng));
	pivot.normalize();
	return pivot*mag;
}

Vector CBoid::wanderDir(float dist, float radius, float angle, float mag)
{
	m_dir.normalized()*dist;
}

Vector CBoid::followPath(Vector pos, float mag)
{

}

Vector CBoid::patrol(Vector pos, float mag)
{

}