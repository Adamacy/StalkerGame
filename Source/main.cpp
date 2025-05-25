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
	sf::Texture wall_tex; 
	if (!wall_tex.loadFromFile("Assets/wall.png")){
		std::cout << "Couldn't load textures";
		return -1;
	}
	wall_tex.setRepeated(true);
	std::vector<sf::Sprite> walls;

	sf::Sprite border_top;
	border_top.setTexture(wall_tex);
	border_top.setPosition(0, -1);
	border_top.setTextureRect(sf::IntRect(0, 0, window.getSize().x, 1));
	
	sf::Sprite border_bottom;
	border_bottom.setTexture(wall_tex);
	border_bottom.setPosition(0, window.getSize().y);
	border_bottom.setTextureRect(sf::IntRect(0, 0, window.getSize().x, 1));

	sf::Sprite border_left;
	border_left.setTexture(wall_tex);
	border_left.setPosition(-1, 0);
	border_left.setTextureRect(sf::IntRect(0, 0, 1, window.getSize().y));

	sf::Sprite border_right;
	border_right.setTexture(wall_tex);
	border_right.setPosition(window.getSize().x, 0);
	border_right.setTextureRect(sf::IntRect(0, 0, 1, window.getSize().y));

	walls.emplace_back(border_top);
	walls.emplace_back(border_bottom);
	walls.emplace_back(border_left);
	walls.emplace_back(border_right);

	player.setTexture(knight_tex);
	player.setPosition(200, 200);
	player.setScale(1, 1);
	player.setBounds(0, window.getSize().x, 0, window.getSize().y);
	sf::Event event;
	while (window.isOpen()) {
		sf::Time elapsed = clock.restart();
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		player.moveInDirection(elapsed, walls);
		window.draw(player);
		for (auto& wall : walls) {
			window.draw(wall);
		}
		window.display();

	}
	return 0;
}