#include "SFML\Graphics.hpp"

#include "Boid.h"

void mySeek(CBoid& _player, Vector& _goal, Vector& _steering, float time);
void myFlee(CBoid& _player, Vector& _enemy, float _radius, Vector& _steering, float _time);
void myArrive(CBoid& _player, Vector& _goal, float _radius, Vector& _steering, float _time);
void myPursue(CBoid& _pursuer, CBoid& _target);
void myEvade(CBoid& _evader, CBoid& _enemy);
void myWanderRandom(CBoid& _obj, Vector& _point, Vector& _steering, float& _time, float deltaTime, int _x, int _y);
void myWanderDir(CBoid& _obj, Vector& _point, Vector& _steering, float& _time, float deltaTime);
void getNewDir(CBoid& obj);
void updateVel(CBoid& obj, Vector& _steering, float time);

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(720, 480), "Steering Behaviors", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setSize(sf::Vector2u(720, 480));
	window.setFramerateLimit(60);
	
	CGameObject g_Goal(OBJECT_TYPE::GOAL);
	g_Goal.setPos(Vector(360, 240));

	CGameObject g_Enemy(OBJECT_TYPE::ENEMY);
	g_Enemy.setPos(Vector(180, 120));

	CBoid g_Player;
	g_Player.setPos(10.0f, 10.0f);

	CBoid player(Vector(g_Player.getPos()), Vector(1, 0));
	bool seek = false;
	bool flee = false;
	bool arrive = false;
	bool wanderRandom = false;
	bool wanderDir = false;

	Vector randomPoint(window.getSize().x, window.getSize().y);

	sf::Clock clock;
	float time = 0;
	sf::Time deltaTime = sf::seconds(0);

	while (window.isOpen())
	{
		deltaTime = clock.restart();
		time += deltaTime.asSeconds();
		sf::Event event;
		Vector newDir;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2f mousePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				g_Goal.setPos(SFMLfToVec(mousePos));
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					newDir = Vector(0, -1);
					//g_Player.rotate((newDir - player.getDir()).angle());
					player.setDir(newDir);
				}
				if (event.key.code == sf::Keyboard::S)
				{
					newDir = Vector(0, 1);
					player.setDir(newDir);
				}
				if (event.key.code == sf::Keyboard::A)
				{
					newDir = Vector(-1, 0);
					player.setDir(newDir);
				}
				if (event.key.code == sf::Keyboard::D)
				{
					newDir = Vector(1, 0);
					player.setDir(newDir);
					player.getDir().angle();
				}
				if (event.key.code == sf::Keyboard::Numpad1)
				{
					seek = !seek;
				}
				if (event.key.code == sf::Keyboard::Numpad2)
				{
					flee = !flee;
				}
				if (event.key.code == sf::Keyboard::Numpad3)
				{
					arrive = !arrive;
				}
				if (event.key.code == sf::Keyboard::Numpad6)
				{
					wanderRandom = !wanderRandom;
				}
				if (event.key.code == sf::Keyboard::Numpad7)
				{
					wanderDir = !wanderDir;
				}
				if (event.key.code == sf::Keyboard::R)
				{
					g_Player.setPos(10, 10);
					player.setPos(Vector(g_Player.getPos()));
					player.setDir(Vector(1, 0));
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					event.type = sf::Event::Closed;
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(102, 102, 255, 255));
		g_Goal.draw(window);
		g_Enemy.draw(window);
		g_Player.draw(window);
		window.display();

		//These lines update the position of the player
		Vector newPos = player.getPos() + (player.getVel() * deltaTime.asSeconds());
		player.setPos(newPos);
		g_Player.setPos(player.getPos());
		g_Player.setDir(player.getDir());

		//These lines will apply the seek behavior
		if (seek)
		{
			Vector goal(g_Goal.getPos());
			mySeek(player, goal, newDir, deltaTime.asSeconds());
		}
		//These lines will apply the flee behavior
		if (flee)
		{
			Vector enemy(g_Enemy.getPos());
			myFlee(player, enemy, g_Enemy.getRadius() + g_Player.getRadius(), newDir, deltaTime.asSeconds());
		}
		if (arrive)
		{
			Vector goal(g_Goal.getPos());
			//myArrive(player, goal, goalRadius.getRadius() + playerRadius.getRadius(), newDir, deltaTime.asSeconds());
		}
		if (wanderRandom)
		{
			myWanderRandom(player, randomPoint, newDir, time, deltaTime.asSeconds(), window.getSize().x - 10, window.getSize().y - 10);
		}
		if (wanderDir)
		{
			myWanderDir(player, randomPoint, newDir, time, deltaTime.asSeconds());
		}
	}

	return 0;
}

void mySeek(CBoid& _player, Vector& _goal, Vector& _steering, float _time)
{
	_steering = _player.seek(_goal, 100.0f);
	updateVel(_player, _steering, _time);
}

void myFlee(CBoid& _player, Vector& _enemy, float _radius, Vector& _steering, float _time)
{
	_steering = _player.flee(_enemy, 150.0f, _radius);
	updateVel(_player, _steering, _time);
}

void myArrive(CBoid& _player, Vector& _goal, float _radius, Vector& _steering, float _time)
{
	_steering = _player.arrive(_goal, 100, _radius);
	//updateVel(_player, _steering, _time);
	Vector vel = _steering - _player.getVel();
	vel /= _time;
	if (vel.length() > _player.getSpeed())
	{
		vel.normalize();
		vel *= _player.getSpeed();
	}
	_player.setVel(vel);
	getNewDir(_player);
}

void myWanderRandom(CBoid& _obj, Vector& _point, Vector& _steering, float& _time, float deltaTime, int _x, int _y)
{
	if (_time > 2.0f)
	{
		_point = _obj.wanderRandom(_x, _y);
		_time = 0;
	}
	mySeek(_obj, _point, _steering, deltaTime);
}

void myWanderDir(CBoid& _obj, Vector& _point, Vector& _steering, float& _time, float deltaTime)
{
	if (_time > 2.0f)
	{
		_point = _obj.wanderDir(50, 20, 30);
		_time = 0;
	}
	mySeek(_obj, _point, _steering, deltaTime);
}

void getNewDir(CBoid& obj)
{
	if (obj.getVel().length() > 0)
		obj.setDir(obj.getVel().normalized());
}

void updateVel(CBoid& obj, Vector& _steering, float _time)
{
	Vector vel = obj.getVel() + (_steering * _time);
	if (vel.length() > obj.getSpeed())
	{
		vel.normalize();
		vel *= obj.getSpeed();
	}
	obj.setVel(vel);
	getNewDir(obj);
}