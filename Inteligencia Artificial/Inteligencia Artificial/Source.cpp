#include "SFML\Graphics.hpp"

#include "Boid.h"

void mySeek(CBoid& _player, Vector& _goal, Vector& _steering, float time);
void myFlee(CBoid& _player, Vector& _enemy, float _radius, Vector& _steering, float _time);
void myArrive(CBoid& _player, Vector& _goal, float _radius, Vector& _steering, float _time);
void myPursue(CBoid& _pursuer, CBoid& _target);
void myEvade(CBoid& _evader, CBoid& _enemy);
void myWanderRandom(CBoid& _obj, Vector& _point, Vector& _steering, float& _time, float deltaTime, int _x, int _y);
void myWanderDir(CBoid& _obj, Vector& _point, Vector& _steering, float& _time, float deltaTime);
void resetRotation(sf::Shape& obj);
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

	sf::CircleShape g_Player(10, 3);
	g_Player.setOrigin(10, 10);
	g_Player.setPosition(10, 10);
	g_Player.setFillColor(sf::Color(0, 255, 0, 255));

	sf::CircleShape playerCenter;
	playerCenter.setRadius(1.0f);
	playerCenter.setFillColor(sf::Color::Black);
	playerCenter.setPosition(g_Player.getPosition());

	sf::CircleShape playerRadius;
	playerRadius.setRadius(10.0f);
	playerRadius.setOrigin(10, 10);
	playerRadius.setFillColor(sf::Color(0, 0, 0, 0));
	playerRadius.setOutlineThickness(1.0f);
	playerRadius.setOutlineColor(sf::Color(0, 0, 0, 255));

	sf::Vertex playerDir[] =
	{
		sf::Vertex(g_Player.getPosition()),
		sf::Vertex(sf::Vector2f(0, 0))
	};

	CBoid player(Vector(g_Player.getPosition().x, g_Player.getPosition().y), Vector(1, 0));
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
					//g_Player.rotate((newDir - player.getDir()).angle());
					player.setDir(newDir);
				}
				if (event.key.code == sf::Keyboard::A)
				{
					newDir = Vector(-1, 0);
					//g_Player.rotate((newDir - player.getDir()).angle());
					player.setDir(newDir);
				}
				if (event.key.code == sf::Keyboard::D)
				{
					newDir = Vector(1, 0);
					//g_Player.rotate((newDir - player.getDir()).angle());
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
					g_Player.setPosition(sf::Vector2f(10, 10));
					player.setPos(Vector(g_Player.getPosition().x, g_Player.getPosition().y));
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

		playerCenter.setPosition(g_Player.getPosition());
		playerRadius.setPosition(g_Player.getPosition());
		playerDir[0].position = sf::Vector2f(player.getPos().x, player.getPos().y);
		playerDir[1].position = sf::Vector2f(player.getDir().x*50.0f, player.getDir().y*50.0f) + playerDir[0].position;

		window.clear(sf::Color(102, 102, 255, 255));
		g_Goal.draw(window);
		g_Enemy.draw(window);
		g_Player.rotate(player.getDir().angle() + 90);
		window.draw(g_Player);
		window.draw(playerCenter);
		window.draw(playerRadius);
		window.draw(playerDir, 2, sf::Lines);
		window.display();

		//This will reset the player rotation to 0
		resetRotation(g_Player);

		//These lines update the position of the player
		Vector newPos = player.getPos() + (player.getVel() * deltaTime.asSeconds());
		player.setPos(newPos);
		g_Player.setPosition(sf::Vector2f(player.getPos().x, player.getPos().y));

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
			myFlee(player, enemy, 50 + playerRadius.getRadius(), newDir, deltaTime.asSeconds());
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

void resetRotation(sf::Shape& obj)
{
	float rot = 0 - obj.getRotation();
	obj.rotate(rot);
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