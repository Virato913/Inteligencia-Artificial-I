#pragma once

#include "SFML\Graphics.hpp"

#include "Vector.h"

#define VecToSFMLf(vector) sf::Vector2f(vector.x, vector.y)
#define VecToSFMLi(vector) sf::Vector2i(vector.x, vector.y)
#define VecToSFMLu(vector) sf::Vector2u(vector.x, vector.y)
#define SFMLfToVec(vector) Vector(vector.x, vector.y)
#define SFMLiToVec(vector) Vector(vector.x, vector.y)
#define SFMLuToVec(vector) Vector(vector.x, vector.y)

enum class OBJECT_TYPE
{
	GOAL,
	ENEMY
};

class CGameObject
{
protected:
	sf::Shape* m_shape;
	sf::CircleShape* m_radius;
	sf::CircleShape* m_center;
	Vector m_pos;

public:
	CGameObject(OBJECT_TYPE type = (OBJECT_TYPE)-1);
	~CGameObject();
	Vector getPos();
	void setPos(Vector pos);
	void draw(sf::RenderWindow& window);
};

