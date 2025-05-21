#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Stalker Game");
	sf::Clock clock;
	while (window.isOpen()) {
		sf::Time elapsed = clock.restart();
		window.clear(sf::Color::Red);
		window.display();
	}
	return 0;
}