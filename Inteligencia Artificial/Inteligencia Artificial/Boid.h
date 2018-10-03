#pragma once

#include "GameObject.h"
#include "Vector.h"

class CBoid : public CGameObject
{
private:
	Vector m_dir;

public:
	CBoid();
	~CBoid();
	Vector getDir();
	void setDir(Vector dir);
	Vector seek(Vector pos, float mag);
	Vector flee(Vector pos, float mag);
	Vector pursue(CBoid other, float time, float mag);
	Vector evade(CBoid other, float time, float mag);
	Vector wanderRandom(float mag);
	Vector wanderDir(float dist, float radius, float angle, float mag);
	Vector followPath(Vector pos, float mag);
	Vector patrol(Vector pos, float mag);
};

