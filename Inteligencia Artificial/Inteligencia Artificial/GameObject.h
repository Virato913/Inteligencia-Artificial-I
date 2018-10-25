#pragma once

#include "Vector.h"

class CGameObject
{
protected:
	Vector m_pos;

public:
	CGameObject();
	~CGameObject();
	Vector getPos();
	void setPos(Vector pos);
};

