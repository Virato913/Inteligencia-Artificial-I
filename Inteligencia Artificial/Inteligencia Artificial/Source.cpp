#include "Boid.h"

int main()
{
	Vector current(4, -3), previous(0, 0);
	CBoid agent;
	agent.setPos(Vector(5,2));
	Vector newDir = agent.followPath(current, previous, 2);
	return 0;
}