#include "GameObject.h"

CGameObject::CGameObject()
{

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