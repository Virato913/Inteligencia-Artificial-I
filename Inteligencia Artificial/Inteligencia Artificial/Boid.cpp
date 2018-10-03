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

}

Vector CBoid::evade(CBoid other, float time, float mag)
{

}

Vector CBoid::wanderRandom(float mag)
{

}

Vector CBoid::wanderDir(float dist, float radius, float angle, float mag)
{

}

Vector CBoid::followPath(Vector pos, float mag)
{

}

Vector CBoid::patrol(Vector pos, float mag)
{

}