#pragma once

#include "GameObject.h"
#include "Vector.h"

#include <random>

class CBoid : public CGameObject
{
private:
	sf::Vertex m_line[2];
	Vector m_dir;
	Vector m_vel;
	float m_speed;

	bool m_seek = false;
	bool m_flee = false;
	bool m_arrive = false;
	bool m_pursue = false;
	bool m_evade = false;
	bool m_wanderRandom = false;
	bool m_wanderDir = false;
	bool m_followPath = false;
	bool m_patrol = false;

	Vector m_seekTarget = Vector(0,0);
	Vector m_fleeTarget = Vector(0,0);
	Vector m_arriveTarget = Vector(0,0);
	Vector m_pursueTarget = Vector(0,0);
	Vector m_evadeTarget = Vector(0,0);
	//Vector m_wanderRandomTarget = Vector(0,0);
	//Vector m_wanderDirTarget = Vector(0,0);
	//Vector m_followPathTarget = Vector(0,0);
	//Vector m_patrolTarget = Vector(0,0);

public:
	CBoid();
	CBoid(Vector pos);
	CBoid(Vector pos, Vector dir);
	~CBoid();
	Vector getDir();
	void setDir(Vector dir);
	void setDir(float x, float y);
	Vector getVel();
	void setVel(Vector vel);
	void setVel(float x, float y);
	float getSpeed();
	void setSpeed(float speed);
	void draw(sf::RenderWindow& window);
	void update(float deltaTime);

	void setSeekState(bool bVal) { m_seek = bVal; }
	void setFleeState(bool bVal) { m_flee = bVal; }
	void setArriveState(bool bVal) { m_arrive = bVal; }
	void setPursueState(bool bVal) { m_pursue = bVal; }
	void setEvadeState(bool bVal) { m_evade = bVal; }
	void setWanderRandomState(bool bVal) { m_wanderRandom = bVal; }
	void setWanderDirState(bool bVal) { m_wanderDir = bVal; }
	void setFollowPathState(bool bVal) { m_followPath = bVal; }
	void setPatrolState(bool bVal) { m_patrol = bVal; }

	void setSeekTarget(Vector& target) { m_seekTarget = target; }
	void setFleeTarget(Vector& target) { m_fleeTarget = target; }
	void setArriveTarget(Vector& target) { m_arriveTarget = target; }
	void setPursueTarget(Vector& target) { m_pursueTarget = target; }
	void setEvadeTarget(Vector& target) { m_evadeTarget = target; }
	//void setWanderRandomTarget(Vector& target) { m_wanderRandomTarget = target; }
	//void setWanderDirTarget(Vector& target) { m_wanderDirTarget = target; }
	//void setFollowPathTarget(Vector& target) { m_followPathTarget = target; }
	//void setPatrolTarget(Vector& target) { m_patrolTarget = target; }

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
