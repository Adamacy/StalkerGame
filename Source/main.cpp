#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Stalker.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int GRID_COLS = 8;
const int GRID_ROWS = 6;
const float WALL_THICKNESS = 20.f;
const float WALL_LENGTH = 90.f;
const int NUM_APPLES = 10;

std::vector<std::pair<int, int>> occupiedCells;

//Random wall generating
sf::Sprite createWall(float x, float y, float horizontal) {
	sf::Sprite wall;
	if (horizontal) {
		wall.setTextureRect(sf::IntRect(0, 0, WALL_LENGTH, WALL_THICKNESS));
	}
	else {
		wall.setTextureRect(sf::IntRect(0, 0, WALL_THICKNESS, WALL_LENGTH));
	}
	wall.setPosition(x, y);
	return wall;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Stalker Game");
	window.setFramerateLimit(60);
	srand(time(0));
	float cellWidth = static_cast<float>(WINDOW_WIDTH) / GRID_COLS;
	float cellHeight = static_cast<float>(WINDOW_HEIGHT) / GRID_ROWS;

	// Textures
	sf::Texture knight_tex;
	if (!knight_tex.loadFromFile("Assets/knight.png")) {
		std::cout << "Couldn't load textures";
		return -1;
	}
	sf::Texture wall_tex;
	if (!wall_tex.loadFromFile("Assets/wall.png")) {
		std::cout << "Couldn't load textures";
		return -1;
	}
	sf::Texture apple_tex;
	if (!apple_tex.loadFromFile("Assets/apple.png")) {
		std::cout << "Couldn't load textures";
		return -1;
	}
	wall_tex.setRepeated(true);
	sf::Font font;
	if (!font.loadFromFile("Assets/roboto.ttf")) {
		std::cout << "Couldn't laod font!";
		return -1;
	}
	sf::Texture stalker_tex;
	if (!stalker_tex.loadFromFile("Assets/stalker.png")) {
		std::cout << "Couldn't laod font!";
		return -1;
	}
	sf::Text text;
	text.setFont(font);
	text.setString("Score: ");
	text.setCharacterSize(24);


	std::vector<sf::Sprite> walls;
	std::vector<sf::Sprite> apples;

	//Generating grid for walls
	for (int row = 0; row < GRID_ROWS; ++row) {
		for (int col = 0; col < GRID_COLS; ++col) {
			int index = row * GRID_COLS + col;
			int choice = rand() % 3;

			float cellX = col * cellWidth;
			float cellY = row * cellHeight;

			if (choice == 1) {
				float x = cellX + (cellWidth - WALL_LENGTH) / 2;
				float y = cellY + (cellHeight - WALL_THICKNESS) / 2;
				walls.push_back(createWall(x, y, true));
				occupiedCells.emplace_back(row, col);
			}
			else if (choice == 2) {
				float x = cellX + (cellWidth - WALL_THICKNESS) / 2;
				float y = cellY + (cellHeight - WALL_LENGTH) / 2;
				walls.push_back(createWall(x, y, false));
				occupiedCells.emplace_back(row, col);
			}
		}
	}
	//Generating apples on not occupied cells
	while (apples.size() < NUM_APPLES) {
		int row = rand() % GRID_ROWS;
		int col = rand() % GRID_COLS;

		if (std::find(occupiedCells.begin(), occupiedCells.end(), std::make_pair(row, col)) != occupiedCells.end()) {
			continue;
		}

		float x = col * cellWidth + cellWidth / 2;
		float y = row * cellHeight + cellHeight / 2;

		sf::Sprite appleSprite;
		appleSprite.setTexture(apple_tex);

		float targetSize = std::min(cellWidth, cellHeight) * 0.3f;
		sf::Vector2u texSize = apple_tex.getSize();
		float scaleX = targetSize / texSize.x;
		float scaleY = targetSize / texSize.y;
		appleSprite.setScale(scaleX, scaleY);

		appleSprite.setPosition(x - targetSize / 2, y - targetSize / 2);

		apples.push_back(appleSprite);
		occupiedCells.emplace_back(row, col);
	}

	sf::Clock clock;
	Player player;
	Stalker stalker;

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

	//Player
	player.setTexture(knight_tex);
	player.setPosition(200, 200);
	player.setScale(1, 1);
	player.setBounds(0, window.getSize().x, 0, window.getSize().y);

	//Stalker
	stalker.setTexture(stalker_tex);
	stalker.setPosition(700, 500);
	stalker.setScale(1.3, 1.3);
	stalker.setBounds(0, window.getSize().x, 0, window.getSize().y);

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
		player.resolveCollisionWithApple(apples, text);
		stalker.followPlayer(player, walls, elapsed);
		if (player.get_score() == NUM_APPLES) {
			sf::Text finish;
			finish.setFont(font);
			finish.setString("You won!");
			finish.setPosition((WINDOW_WIDTH / 2) - 60, (WINDOW_HEIGHT / 2) - 50);
			window.draw(finish);
			
		}
		else if (player.resolveCollisionWithStalker(stalker)) {
			sf::Text finish;
			finish.setFont(font);
			finish.setString("You lost!");
			finish.setPosition((WINDOW_WIDTH / 2) - 60, (WINDOW_HEIGHT / 2) - 50);
			window.draw(finish);
		}
		else {
			for (auto& wall : walls) {
				wall.setTexture(wall_tex);
				window.draw(wall);
			}
			for (auto& apple : apples) {
				window.draw(apple);
			}
			window.draw(text);
			window.draw(player);
			window.draw(stalker);
		}
		
		window.display();
	}
	return 0;
}