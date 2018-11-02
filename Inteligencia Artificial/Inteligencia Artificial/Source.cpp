#include "SFML\Graphics.hpp"

#include "Boid.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(720, 480), "Steering Behaviors", sf::Style::Default, settings);
	window.setSize(sf::Vector2u(720, 480));

	sf::RectangleShape g_Background;
	g_Background.setSize(sf::Vector2f(720, 480));
	g_Background.setFillColor(sf::Color(102, 102, 255, 255));
	g_Background.setOutlineColor(sf::Color::Black);

	sf::CircleShape g_Goal;
	g_Goal.setRadius(12);
	g_Goal.setOrigin(12, 12);
	g_Goal.setPosition(360, 240);
	g_Goal.setFillColor(sf::Color(255, 0, 0, 255));

	sf::CircleShape goalCenter;
	goalCenter.setRadius(1.0f);
	goalCenter.setFillColor(sf::Color::Black);
	goalCenter.setPosition(g_Goal.getPosition());

	sf::CircleShape goalRadius(80);
	goalRadius.setOrigin(80, 80);
	goalRadius.setFillColor(sf::Color(0, 0, 0, 0));
	goalRadius.setOutlineThickness(1.0f);
	goalRadius.setOutlineColor(sf::Color(0, 0, 0, 255));

	sf::CircleShape g_Enemy(12, 4);
	g_Enemy.setOrigin(12, 12);
	g_Enemy.setPosition(130, 120);
	g_Enemy.setFillColor(sf::Color(0, 0, 255, 255));

	sf::CircleShape enemyRadius(60);
	enemyRadius.setOrigin(60, 60);
	enemyRadius.setFillColor(sf::Color(0, 0, 0, 0));
	enemyRadius.setOutlineThickness(1.0f);
	enemyRadius.setOutlineColor(sf::Color(0, 0, 0, 255));
	enemyRadius.setPosition(g_Enemy.getPosition());

	sf::CircleShape g_Player(12, 3);
	g_Player.setOrigin(12, 12);
	g_Player.setPosition(12, 12);
	g_Player.setFillColor(sf::Color(0, 255, 0, 255));

	sf::CircleShape playerCenter;
	playerCenter.setRadius(1.0f);
	playerCenter.setFillColor(sf::Color::Black);
	playerCenter.setPosition(g_Player.getPosition());

	sf::CircleShape playerRadius;
	playerRadius.setRadius(12.0f);
	playerRadius.setOrigin(12, 12);
	playerRadius.setFillColor(sf::Color(0, 0, 0, 0));
	playerRadius.setOutlineThickness(1.0f);
	playerRadius.setOutlineColor(sf::Color(0, 0, 0, 255));

	sf::Vertex playerDir[] =
	{
		sf::Vertex(g_Player.getPosition()),
		sf::Vertex(sf::Vector2f(0, 0))
	};

	CBoid player(Vector(g_Player.getPosition().x, g_Player.getPosition().y));
	bool seek = false;
	bool flee = false;
	bool arrive = false;

	while (window.isOpen())
	{
		sf::Event event;
		Vector newDir;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2f mousePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				g_Goal.setPosition(mousePos);
				goalCenter.setPosition(g_Goal.getPosition());
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
				if (event.key.code == sf::Keyboard::R)
				{
					g_Player.setPosition(sf::Vector2f(12, 12));
					player.setPos(Vector(g_Player.getPosition().x, g_Player.getPosition().y));
					player.setDir(Vector(0, 0));
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					event.type = sf::Event::Closed;
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		goalRadius.setPosition(g_Goal.getPosition());
		playerCenter.setPosition(g_Player.getPosition());
		playerRadius.setPosition(g_Player.getPosition());
		playerDir[0].position = sf::Vector2f(player.getPos().x, player.getPos().y);
		playerDir[1].position = sf::Vector2f(player.getDir().x*50.0f, player.getDir().y*50.0f) + playerDir[0].position;

		window.clear();
		window.draw(g_Background);
		window.draw(g_Goal);
		window.draw(g_Enemy);
		window.draw(enemyRadius);
		g_Player.rotate(player.getDir().angle() + 90);
		window.draw(g_Player);
		window.draw(goalCenter);
		window.draw(goalRadius);
		window.draw(playerCenter);
		window.draw(playerRadius);
		window.draw(playerDir, 2, sf::Lines);
		window.display();

		//This will reset the player rotation to 0
		float rot = 0 - g_Player.getRotation();
		g_Player.rotate(rot);

		//These lines update the position of the player
		//if (player.getDir() != Vector(0, 0))
		//{
		//	//Vector newPos = player.getPos() + player.getVel();
		//	Vector newPos = player.getPos() + (player.getDir() * 0.2f);
		//	player.setPos(newPos);
		//	g_Player.setPosition(sf::Vector2f(player.getPos().x, player.getPos().y));
		//}

		if (player.getDir() != Vector(0, 0))
		{
			Vector newPos = player.getPos() + player.getVel();
			player.setPos(newPos);
			g_Player.setPosition(sf::Vector2f(player.getPos().x, player.getPos().y));
		}

		//These lines will apply the seek behavior
		if (seek)
		{
			//Vector goal(g_Goal.getPosition().x, g_Goal.getPosition().y);
			//Vector desVel = player.seek(goal, 5.0f);
			//Vector steering = desVel - player.getVel();
			//steering.normalize();
			//steering *= 5.0f;
			//Vector newVel = player.getVel() + steering;
			//newVel.normalize();
			//newVel *= player.getSpeed();
			//player.setDir(newVel.normalized());
			//player.setVel(newVel);
			//newDir += player.getDir();
			//newDir.normalize();
			//player.setDir(newDir);

			Vector goal(g_Goal.getPosition().x, g_Goal.getPosition().y);
			Vector newDir = player.seek(goal, 5.0f);
			newDir += player.getDir();
			newDir.normalize();
			player.setDir(newDir);
		}
		//These lines will apply the flee behavior
		if (flee)
		{
			//Vector enemy(g_Enemy.getPosition().x, g_Enemy.getPosition().y);
			//Vector desVel = player.flee(enemy, 5.0f, enemyRadius.getRadius() + playerRadius.getRadius());
			//Vector steering = desVel - player.getVel();
			//steering.normalize();
			//steering *= 5.0f;
			//Vector newVel = player.getVel() + steering;
			//newVel.normalize();
			//newVel *= player.getSpeed();
			//player.setDir(newVel.normalized());
			//player.setVel(newVel);
			//newDir += player.getDir();
			//newDir.normalize();
			//player.setDir(newDir);

			Vector enemy(g_Enemy.getPosition().x, g_Enemy.getPosition().y);
			Vector newDir = player.flee(enemy, 5.0f, enemyRadius.getRadius() + playerRadius.getRadius());
			//if (newDir.length() > 0)
			//{
				newDir += player.getDir();
				newDir.normalize();
				player.setDir(newDir);
			//}
			//else
			//	player.setDir(Vector(0, 0));
		}
		if (arrive)
		{
			//Vector goal(g_Goal.getPosition().x, g_Goal.getPosition().y);
			//Vector newDir = player.arrive(goal, 5.0f, goalRadius.getRadius());
			//newDir += player.getDir();
			//newDir.normalize();
			//player.setDir(newDir);
			Vector goal(g_Goal.getPosition().x, g_Goal.getPosition().y);
			Vector vel = player.arrive(goal, 500.0f, goalRadius.getRadius() + playerRadius.getRadius());
			if (vel.length() > 0.05f)
			{
				Vector newVel = vel - player.getVel();
				player.setSpeed(1.0f);
				player.setVel((player.getVel() + newVel).normalized()*player.getSpeed());
				player.setDir(player.getVel().normalized());
			}
			else
			{
				Vector newVel = vel - player.getVel();
				player.setSpeed(0.0f);
				player.setVel((player.getVel() + newVel).normalized()*player.getSpeed());
				player.setDir(player.getVel().normalized());
			}
		}
	}

	return 0;
}