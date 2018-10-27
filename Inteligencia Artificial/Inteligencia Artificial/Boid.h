#pragma once

#include "GameObject.h"
#include "Vector.h"

#include <random>

class CBoid : public CGameObject
{
private:
	Vector m_dir;

public:
	CBoid();
	~CBoid();
	Vector getDir();
	void setDir(Vector dir);
	Vector seek(Vector pos, float mag = 1);
	Vector flee(Vector pos, float mag = 1, float radius = 0);
	Vector pursue(CBoid other, float time, float mag = 1);
	Vector evade(CBoid other, float time, float mag = 1);
	Vector wanderRandom(float mag = 1);
	Vector wanderDir(float dist, float radius, float angle, float mag = 1);
	Vector followPath(Vector currentNode, Vector previousNode, float mag = 1);
	Vector patrol(Vector pos, float mag = 1);
};

