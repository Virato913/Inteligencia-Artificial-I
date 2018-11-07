#include "GameObject.h"

CGameObject::CGameObject(OBJECT_TYPE type)
{
	switch (type)
	{
	case OBJECT_TYPE::GOAL:
		m_shape = new sf::CircleShape(10.0f, 5);
		m_shape->setFillColor(sf::Color(255, 0, 0, 255));
		break;
	case OBJECT_TYPE::ENEMY:
		m_shape = new sf::CircleShape(10.0f, 4);
		m_shape->setFillColor(sf::Color(0, 0, 255, 255));
		break;
	default:
		m_shape = new sf::CircleShape(10.0f);
		break;
	}
	m_shape->setOrigin(10.0f, 10.0f);
	switch (type)
	{
	case OBJECT_TYPE::GOAL:
		m_radius = new sf::CircleShape(80.0f);
		m_radius->setOrigin(80.0f, 80.0f);
		break;
	case OBJECT_TYPE::ENEMY:
		m_radius = new sf::CircleShape(50.0f);
		m_radius->setOrigin(50.0f, 50.0f);
		break;
	default:
		m_radius = new sf::CircleShape(10.0f);
		m_radius->setOrigin(10.0f, 10.0f);
		break;
	}
	m_radius->setFillColor(sf::Color(0, 0, 0, 0));
	m_radius->setOutlineThickness(1.0f);
	m_radius->setOutlineColor(sf::Color(0, 0, 0, 255));
	m_center = new sf::CircleShape(1.0f);
	m_center->setFillColor(sf::Color(0, 0, 0, 255));
	m_pos = Vector(0, 0);
}

CGameObject::~CGameObject()
{
	if (m_shape)
		delete m_shape;
	if (m_radius)
		delete m_radius;
	if (m_center)
		delete m_center;
}

Vector CGameObject::getPos()
{
	return m_pos;
}

void CGameObject::setPos(Vector pos)
{
	m_pos = pos;
	m_shape->setPosition(VecToSFMLf(m_pos));
	m_center->setPosition(VecToSFMLf(m_pos));
	m_radius->setPosition(VecToSFMLf(m_pos));
}

void CGameObject::setPos(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
	m_shape->setPosition(VecToSFMLf(m_pos));
	m_center->setPosition(VecToSFMLf(m_pos));
	m_radius->setPosition(VecToSFMLf(m_pos));
}

float CGameObject::getRadius()
{
	return m_radius->getRadius();
}

void CGameObject::setRadius(float radius)
{
	m_radius->setRadius(radius);
	m_radius->setOrigin(radius, radius);
}

void CGameObject::draw(sf::RenderWindow& window)
{
	window.draw(*m_shape);
	window.draw(*m_center);
	window.draw(*m_radius);
}