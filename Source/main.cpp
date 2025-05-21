#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Stalker Game");
	window.setFramerateLimit(60);
	sf::Clock clock;
	Player player;
	sf::Texture knight_tex;
	if (!knight_tex.loadFromFile("Assets/knight.png")) {
		std::cout << "Couldn't load textures";
		return -1;
	}
	player.setTexture(knight_tex);
	player.setPosition(200, 200);
	player.setScale(1.5, 1.5);
	sf::Event event;
	while (window.isOpen()) {
		sf::Time elapsed = clock.restart();
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		player.setBounds(0, window.getSize().x, 0, window.getSize().y);
		player.moveInDirection(elapsed, std::vector<sf::Sprite>());
		window.draw(player);
		window.display();
		

	}
	return 0;
}