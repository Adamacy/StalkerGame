#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

class Stalker : public sf::Sprite {
public:

    void followPlayer(const sf::Sprite& player,
        const std::vector<sf::Sprite>& walls,
        sf::Time& deltaTime)
    {
        sf::Vector2f direction = player.getPosition() - getPosition();

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length == 0) return;

        direction /= length;

        sf::Vector2f movement = sf::Vector2f(direction.x * speed * deltaTime.asSeconds(), direction.y * speed * deltaTime.asSeconds());

        sf::Vector2f currentPos = getPosition();
        sf::Vector2f newPos = currentPos + movement;

        sf::FloatRect stalkerBounds = getGlobalBounds();
        stalkerBounds.left = newPos.x;
        stalkerBounds.top = newPos.y;

        for (const auto& wall : walls) {
            if (stalkerBounds.intersects(wall.getGlobalBounds())) {

                return;
            }
        }
        move(movement);
    }

	void setBounds(int left, int right, int top, int bottom)
	{
		bound_top = top;
		bound_bottom = bottom;
		bound_right = right;
		bound_left = left;
	}
private:
	int speed = 150.f;
	int bound_top = 0;
	int bound_bottom = 0;
	int bound_left = 0;
	int bound_right = 0;
};