#include "SFML\Graphics.hpp"

#include "Boid.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(720, 480), "Steering Behaviors");
	window.setSize(sf::Vector2u(720, 480));

	sf::RectangleShape g_Background;
	g_Background.setSize(sf::Vector2f(720,480));
	g_Background.setFillColor(sf::Color(102,102,255,255));
	g_Background.setOutlineColor(sf::Color::Black);

	sf::CircleShape g_Goal;
	g_Goal.setRadius(12);
	g_Goal.setOrigin(12, 12);
	g_Goal.setPosition(360, 240);
	g_Goal.setFillColor(sf::Color(255,0,0,255));

	sf::ConvexShape g_Player;
	g_Player.setPointCount(3);
	g_Player.setPoint(0, sf::Vector2f(0, 24));
	g_Player.setPoint(1, sf::Vector2f(24, 24));
	g_Player.setPoint(2, sf::Vector2f(12, 0));
	g_Player.setOrigin(12, 12);
	g_Player.setPosition(12, 12);
	g_Player.rotate(90);
	g_Player.setFillColor(sf::Color(0, 255, 0, 255));

	sf::CircleShape goalCenter;
	goalCenter.setRadius(1.0f);
	goalCenter.setFillColor(sf::Color::Black);
	goalCenter.setPosition(g_Goal.getPosition());

	//sf::CircleShape playerCenter;
	//goalCenter.setRadius(1.0f);
	//goalCenter.setFillColor(sf::Color::Black);
	//goalCenter.setPosition(g_Player.getPosition());

	CBoid player(Vector(g_Player.getPosition().x, g_Player.getPosition().y));
	bool seek = false;

	while (window.isOpen())
	{
		sf::Event event;
		Vector newDir;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					newDir = Vector(0, -1);
					g_Player.rotate((newDir - player.getDir()).angle());
					player.setDir(newDir);
				}
				if (event.key.code == sf::Keyboard::S)
				{
					newDir = Vector(0, 1);
					g_Player.rotate((newDir - player.getDir()).angle());
					player.setDir(newDir);
				}
				if (event.key.code == sf::Keyboard::A)
				{
					newDir = Vector(-1, 0);
					g_Player.rotate((newDir - player.getDir()).angle());
					player.setDir(newDir);
				}
				if (event.key.code == sf::Keyboard::D)
				{
					newDir = Vector(1, 0);
					g_Player.rotate((newDir - player.getDir()).angle());
					player.setDir(newDir);
				}
				if (event.key.code == sf::Keyboard::Numpad1)
				{
					seek = !seek;
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

		window.clear();
		window.draw(g_Background);
		window.draw(g_Goal);
		window.draw(g_Player);
		window.draw(goalCenter);
		//window.draw(playerCenter);
		window.display();

		//These lines update the possition of the player
		//0.05f is the velocity at which the player travels
		Vector newPos = player.getPos() + (player.getDir() * 0.1f);
		player.setPos(newPos);
		g_Player.setPosition(sf::Vector2f(player.getPos().x, player.getPos().y));

		//These lines will apply the seek behavior
		if (seek)
		{
			Vector goal(g_Goal.getPosition().x, g_Goal.getPosition().y);
			Vector newDir = player.seek(goal);
			newDir += player.getDir();
			newDir.normalize();
			g_Player.rotate((newDir - player.getDir()).angle() + 180);
			player.setDir(newDir);
		}
	}

	return 0;
}