#include "Boid.h"

CBoid::CBoid()
{
	m_dir = Vector(0, 0);
}

CBoid::CBoid(Vector pos)
{
	m_pos = pos;
}

CBoid::CBoid(Vector pos, Vector dir)
{
	m_pos = pos;
	m_dir = dir;
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
	Vector seekForce = pos - m_pos;
	seekForce.normalize();
	return seekForce * mag;
}

Vector CBoid::flee(Vector pos, float mag, float radius)
{
	Vector fleeForce = m_pos - pos;
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
	Vector evadeForce = flee(other.getDir()*time, mag) + flee(other.m_pos, mag);
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
	//Get the projected point
	Vector projectedPoint = m_pos + (m_dir.normalized() * dist);
	//Get a random angle within the circle
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<> distr(m_dir.angle() - (angle / 2), m_dir.angle() + (angle / 2));
	float newAngle = distr(eng) * PI / 180;
	Vector pivot(cos(newAngle) * radius, sin(newAngle) * radius);
	//Get the final point
	Vector finalPoint = projectedPoint + pivot;
	Vector dir = finalPoint - m_pos;
	dir.normalize();
	return dir * mag;
}

Vector CBoid::followPath(Vector currentNode, Vector previousNode, float mag)
{
	Vector nodeLine = currentNode - previousNode;
	Vector pos = m_pos - previousNode;
	Vector seekNode = seek(currentNode);
	seekNode.normalize();
	Vector proj = pos.projection(nodeLine);
	Vector projDir = proj - m_pos;
	projDir.normalize();
	Vector pivot = seekNode + projDir;
	pivot.normalize();
	return pivot * mag;
}

Vector CBoid::patrol(Vector pos, float mag)
{
	return Vector();
}