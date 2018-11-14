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
	setPos(Vector(0, 0));
	setVel(Vector(0, 0));
	setDir(Vector(0, 0));
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
	setPos(pos);
	setVel(Vector(0, 0));
	setDir(Vector(0, 0));
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
	setPos(pos);
	setVel(Vector(0, 0));
	setDir(dir);
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

void CBoid::setDir(float x, float y)
{
	setDir(Vector(x, y));
}

Vector CBoid::getVel()
{
	return m_vel;
}

void CBoid::setVel(Vector vel)
{
	m_vel = vel;
	if (m_vel.length() != 0)
		setDir(m_vel.normalized());
}

void CBoid::setVel(float x, float y)
{
	setVel(Vector(x, y));
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

void CBoid::update(float deltaTime)
{
	static float time = 0;
	time += deltaTime;
	Vector steering;
	if (m_seek)
	{
		steering += seek(m_seekTarget->getPos(), 100.0f);
	}
	if (m_flee)
	{
		steering += flee(m_fleeTarget->getPos(), 250.0f, 60.0f);
	}
	if (m_arrive)
	{
		steering += (arrive(m_arriveTarget->getPos(), 100.0f, 90.0f) * 2.5f);
	}
	if (m_pursue)
	{
		steering += pursue(*m_pursueTarget, 1.0f, 200.0f);
	}
	if (m_evade)
	{
		steering += evade(*m_evadeTarget, 1.0f, 200.0f);
	}
	if (m_wanderRandom)
	{
		if (time > 2.0f)
		{
			steering += wanderRandom() * m_speed;
			time = 0;
		}
	}
	if (m_wanderDir)
	{
		if (time > 2.0f)
		{
			steering += wanderDir(50.0f, 60.0f, 90.0f);
			time = 0;
		}
	}
	if (m_followPath)
	{

	}
	if (m_patrol)
	{

	}
	Vector vel = (m_vel + (steering * deltaTime)).truncate(m_speed);
	if (vel.length() > 1.0f)
		setVel(vel);
	else
		setVel(0, 0);
	Vector pos = m_pos + (m_vel * deltaTime);
	if (pos.x < 0)
		pos.x += 720;
	if (pos.x > 720)
		pos.x -= 720;
	if (pos.y < 0)
		pos.y += 480;
	if (pos.y > 480)
		pos.y -= 480;
	setPos(pos);
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
		if (fleeForce.length() <= radius)
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
	return (arriveForce - m_vel);
}

Vector CBoid::pursue(CBoid& other, float time, float mag)
{
	Vector dir = other.getPos() - m_pos;
	float dist = dir.length();
	float predict = time;
	if (m_vel.length() > (dist / time))
		predict = dist / m_vel.length();
	Vector pursueForce = other.getPos() + (other.getVel() * predict);
	return (arrive(pursueForce, mag, 36.0f) * 2.5f);
}

Vector CBoid::evade(CBoid& other, float time, float mag)
{
	Vector dir = other.getPos() - m_pos;
	float dist = dir.length();
	float predict = time;
	if (m_vel.length() > (dist / time))
		predict = dist / m_vel.length();
	Vector evadeForce = other.getPos() + (other.getVel() * predict);
	return flee(evadeForce, mag, 50.0f);
}

Vector CBoid::wanderRandom()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(-1, 1);
	Vector pivot(distr(eng), distr(eng));
	pivot *= m_speed;
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
	Vector dir = finalPoint - m_pos;
	dir.normalize();
	dir *= m_speed;
	return dir;
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
