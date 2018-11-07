#include "Boid.h"

CBoid::CBoid()
{
	m_shape = new sf::CircleShape(10.0f, 3);
	m_shape->setFillColor(sf::Color(0, 255, 0, 255));
	m_shape->setOrigin(10.0f, 10.0f);
	m_radius = new sf::CircleShape(10.0f);
	m_radius->setOrigin(10.0f, 10.0f);
	m_radius->setFillColor(sf::Color(0, 0, 0, 0));
	m_radius->setOutlineThickness(1.0f);
	m_radius->setOutlineColor(sf::Color(0, 0, 0, 255));
	m_center = new sf::CircleShape(1.0f);
	m_center->setFillColor(sf::Color(0, 0, 0, 255));
	m_pos = Vector(0, 0);
	m_dir = Vector(0, 0);
	m_vel = Vector(0, 0);
	m_speed = 100.0f;
}

CBoid::CBoid(Vector pos)
{
	m_shape = new sf::CircleShape(10.0f, 3);
	m_shape->setFillColor(sf::Color(0, 255, 0, 255));
	m_shape->setOrigin(10.0f, 10.0f);
	m_radius = new sf::CircleShape(10.0f);
	m_radius->setOrigin(10.0f, 10.0f);
	m_radius->setFillColor(sf::Color(0, 0, 0, 0));
	m_radius->setOutlineThickness(1.0f);
	m_radius->setOutlineColor(sf::Color(0, 0, 0, 255));
	m_center = new sf::CircleShape(1.0f);
	m_center->setFillColor(sf::Color(0, 0, 0, 255));
	m_pos = pos;
	m_shape->setPosition(VecToSFMLf(m_pos));
	m_center->setPosition(VecToSFMLf(m_pos));
	m_radius->setPosition(VecToSFMLf(m_pos));
	m_dir = Vector(0, 0);
	m_vel = Vector(0, 0);
	m_speed = 100.0f;
}

CBoid::CBoid(Vector pos, Vector dir)
{
	m_shape = new sf::CircleShape(10.0f, 3);
	m_shape->setFillColor(sf::Color(0, 255, 0, 255));
	m_shape->setOrigin(10.0f, 10.0f);
	m_radius = new sf::CircleShape(10.0f);
	m_radius->setOrigin(10.0f, 10.0f);
	m_radius->setFillColor(sf::Color(0, 0, 0, 0));
	m_radius->setOutlineThickness(1.0f);
	m_radius->setOutlineColor(sf::Color(0, 0, 0, 255));
	m_center = new sf::CircleShape(1.0f);
	m_center->setFillColor(sf::Color(0, 0, 0, 255));
	m_pos = pos;
	m_shape->setPosition(VecToSFMLf(m_pos));
	m_center->setPosition(VecToSFMLf(m_pos));
	m_radius->setPosition(VecToSFMLf(m_pos));
	m_dir = dir;
	m_line[0].position = VecToSFMLf(m_pos);
	m_line[1].position = VecToSFMLf((m_dir * 50.0f)) + m_line[0].position;
	m_vel = Vector(0, 0);
	m_speed = 100.0f;
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
	m_line[0].position = VecToSFMLf(m_pos);
	m_line[1].position = VecToSFMLf((m_dir * 50.0f)) + m_line[0].position;
}

Vector CBoid::getVel()
{
	return m_vel;
}

void CBoid::setVel(Vector vel)
{
	m_vel = vel;
}

float CBoid::getSpeed()
{
	return m_speed;
}

void CBoid::setSpeed(float speed)
{
	m_speed = speed;
}

void CBoid::draw(sf::RenderWindow& window)
{
	m_shape->setRotation(getDir().angle() + 90);
	window.draw(*m_shape);
	window.draw(*m_center);
	window.draw(*m_radius);
	window.draw(m_line, 2, sf::Lines);
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
		if (fleeForce.length() < radius)
			fleeForce.normalize();
		else
			fleeForce *= 0;
	}
	else
		fleeForce.normalize();
	return fleeForce * mag;
}

Vector CBoid::arrive(Vector pos, float mag, float radius)
{
	Vector arriveForce = pos - m_pos;
	float dist = arriveForce.length();
	arriveForce.normalize();
	arriveForce *= mag;
	if (dist < radius)
	{
		arriveForce *= (dist / radius);
	}
	return arriveForce;
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

Vector CBoid::wanderRandom(int _x, int _y)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distrx(12, _x);
	std::uniform_int_distribution<> distry(12, _y);
	Vector pivot(distrx(eng), distry(eng));
	return pivot;
}

Vector CBoid::wanderDir(float dist, float radius, float angle, float mag)
{
	//Get the projected point
	Vector projectedPoint = m_pos + (m_dir.normalized() * dist);
	//Get a random angle within the circle
	std::random_device rd;
	std::mt19937 eng(rd());
	float minAngle = m_dir.angle() - (angle / 2);
	float maxAngle = m_dir.angle() + (angle / 2);
	std::uniform_real_distribution<> distr(minAngle, maxAngle);
	float newAngle = distr(eng);
	newAngle *= (PI / 180);
	Vector pivot(cos(newAngle) * radius, sin(newAngle) * radius);
	//Get the final point
	Vector finalPoint = projectedPoint + pivot;
	//Vector dir = finalPoint - m_pos;
	//dir.normalize();
	return finalPoint;
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