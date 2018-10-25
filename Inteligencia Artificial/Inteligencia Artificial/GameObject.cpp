#include "GameObject.h"

CGameObject::CGameObject()
{
	m_pos = Vector(0, 0);
}

CGameObject::~CGameObject()
{

}

Vector CGameObject::getPos()
{
	return m_pos;
}

void CGameObject::setPos(Vector pos)
{
	m_pos = pos;
}