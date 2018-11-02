#pragma once

#include "GameObject.h"
#include "Vector.h"

#include <random>

class CBoid : public CGameObject
{
private:
	Vector m_dir;
	Vector m_vel;
	float m_speed;

public:
	CBoid();
	CBoid(Vector pos);
	CBoid(Vector pos, Vector dir);
	~CBoid();
	Vector getDir();
	void setDir(Vector dir);
	Vector getVel();
	void setVel(Vector vel);
	float getSpeed();
	void setSpeed(float speed);

	Vector seek(Vector pos, float mag = 1);
	Vector flee(Vector pos, float mag = 1, float radius = 0);
	Vector arrive(Vector pos, float mag = 1, float radius = 1);
	Vector pursue(CBoid other, float time, float mag = 1);
	Vector evade(CBoid other, float time, float mag = 1);
	Vector wanderRandom(int _x, int _y);
	Vector wanderDir(float dist, float radius, float angle, float mag = 1);
	Vector followPath(Vector currentNode, Vector previousNode, float mag = 1);
	Vector patrol(Vector pos, float mag = 1);
};

