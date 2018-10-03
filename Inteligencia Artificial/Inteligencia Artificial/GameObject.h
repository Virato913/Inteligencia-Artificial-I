#pragma once

#include "Vector.h"

class CGameObject
{
private:
	Vector m_pos;

public:
	CGameObject();
	~CGameObject();
	Vector getPos();
	void setPos(Vector pos);
};

