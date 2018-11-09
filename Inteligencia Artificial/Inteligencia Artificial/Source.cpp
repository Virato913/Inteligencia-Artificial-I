#include "SFML\Graphics.hpp"

#include "Boid.h"
#include <iostream>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(720, 480), "Steering Behaviors", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setSize(sf::Vector2u(720, 480));
	window.setFramerateLimit(60);
	
	CGameObject g_Goal(OBJECT_TYPE::GOAL);
	g_Goal.setPos(360, 240);

	CGameObject g_Enemy(OBJECT_TYPE::ENEMY);
	g_Enemy.setPos(180, 120);

	CBoid g_Player;
	g_Player.setPos(10, 10);		

	CBoid g_Chaser;
	g_Chaser.setPos(710, 10);

	sf::Text text;

	bool seek = false;
	bool flee = false;
	bool arrive = false;
	bool pursue = false;
	bool evade = false;
	bool wanderRandom = false;
	bool wanderDir = false;

	Vector randomPoint(window.getSize().x, window.getSize().y);

	sf::Clock clock;
	float time = 0;
	sf::Time deltaTime = sf::seconds(0);

	while (window.isOpen())
	{
		system("CLS");
		std::cout << "m_pos: " << g_Player.getPos().x << ", " << g_Player.getPos().y << std::endl;
		std::cout << "m_vel: " << g_Player.getVel().x << ", " << g_Player.getVel().y << std::endl;
		std::cout << "m_dir: " << g_Player.getDir().x << ", " << g_Player.getDir().y << std::endl;

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
					
				}
				if (event.key.code == sf::Keyboard::S)
				{
					
				}
				if (event.key.code == sf::Keyboard::A)
				{
					
				}
				if (event.key.code == sf::Keyboard::D)
				{
					
				}
				if (event.key.code == sf::Keyboard::Numpad1)
				{
					seek = !seek;
					g_Player.setSeekState(seek);
					g_Player.setSeekTarget(&g_Goal);
				}
				if (event.key.code == sf::Keyboard::Numpad2)
				{
					flee = !flee;
					g_Player.setFleeState(flee);
					g_Player.setFleeTarget(&g_Enemy);
				}
				if (event.key.code == sf::Keyboard::Numpad3)
				{
					arrive = !arrive;
					g_Player.setArriveState(arrive);
					g_Player.setArriveTarget(&g_Goal);
				}
				if (event.key.code == sf::Keyboard::Numpad4)
				{
					pursue = !pursue;
					g_Chaser.setPursueState(pursue);
					g_Chaser.setPursueTarget(&g_Player);
				}
				if (event.key.code == sf::Keyboard::Numpad5)
				{
					evade = !evade;
					g_Player.setEvadeState(evade);
					g_Player.setEvadeTarget(&g_Chaser);
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
					g_Player.setVel(0, 0);
					g_Player.setDir(0, 0);
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					event.type = sf::Event::Closed;
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		g_Player.update(deltaTime.asSeconds());
		g_Chaser.update(deltaTime.asSeconds());
		
		window.clear(sf::Color(102, 102, 255, 255));
		g_Goal.draw(window);
		g_Enemy.draw(window);
		g_Player.draw(window);
		g_Chaser.draw(window);
		window.display();
	}
	return 0;
}
