#include "SFML\Graphics.hpp"

#include "Boid.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(720, 480), "Steering Behaviors");
	window.setSize(sf::Vector2u(720, 480));

	sf::RectangleShape g_Background;
	g_Background.setSize(sf::Vector2f(720,480));
	g_Background.setFillColor(sf::Color(102,102,255,255));

	sf::CircleShape g_Goal;
	g_Goal.setRadius(12);
	g_Goal.setOrigin(6, 6);
	g_Goal.setPosition(360, 240);
	g_Goal.setFillColor(sf::Color::Red);

	sf::ConvexShape g_Player;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(g_Background);
		window.draw(g_Goal);
		window.display();
	}

	return 0;
}