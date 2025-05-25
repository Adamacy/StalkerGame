#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Player : public sf::Sprite
{
public:

    
    void setBounds(int left, int right, int top, int bottom)
    {
        bound_top = top;
        bound_bottom = bottom;
        bound_right = right;
        bound_left = left;
    }
    void resolveCollisionWithWalls(const std::vector<sf::Sprite>& obstacles, float move_x, float move_y)
    {
        move(move_x, 0);
        for (const auto& wall : obstacles)
        {
            if (getGlobalBounds().intersects(wall.getGlobalBounds()))
            {
                auto playerBounds = getGlobalBounds();
                auto wallBounds = wall.getGlobalBounds();

                if (move_x > 0)
                {
                    float overlap = (playerBounds.left + playerBounds.width) - wallBounds.left;
                    move(-overlap, 0);
                }
                else if (move_x < 0)
                {
                    float overlap = (wallBounds.left + wallBounds.width) - playerBounds.left;
                    move(overlap, 0);
                }
            }
        }

        move(0, move_y);
        for (const auto& wall : obstacles)
        {
            if (getGlobalBounds().intersects(wall.getGlobalBounds()))
            {
                auto playerBounds = getGlobalBounds();
                auto wallBounds = wall.getGlobalBounds();

                if (move_y > 0)
                {
                    float overlap = (playerBounds.top + playerBounds.height) - wallBounds.top;
                    move(0, -overlap);
                }
                else if (move_y < 0)
                {
                    float overlap = (wallBounds.top + wallBounds.height) - playerBounds.top;
                    move(0, overlap);
                }
            }
        }
    }
    void resolveCollisionWithApple(std::vector<sf::Sprite>& apples, sf::Text& text) {
        
        for (auto it = apples.begin(); it != apples.end(); ) {
            sf::FloatRect player_bounds = getGlobalBounds();
            sf::FloatRect apple_bounds = it->getGlobalBounds();

            if (player_bounds.intersects(apple_bounds)) {
                score++;
                std::cout << "Score: " + std::to_string(score) << "\n";
                text.setString("Score: " + std::to_string(score));

                it = apples.erase(it); //  Safely erase and advance iterator
            }
            else {
                ++it; //  Only increment if not erasing
            }
        }
    }
    void moveInDirection(const sf::Time& elapsed, const std::vector<sf::Sprite>& obstacles)
    {

        float dt = elapsed.asSeconds();

        float move_x = 0.f;
        float move_y = 0.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) move_y -= vertical_speed_ * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) move_y += vertical_speed_ * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) move_x -= horizontal_speed_ * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) move_x += horizontal_speed_ * dt;

        resolveCollisionWithWalls(obstacles, move_x, move_y);
    }
    int get_score() {
        return score;
    }
private:
    int score = 0;
    int m_speed_x = 200;
    int m_speed_y = 200;
    int bound_top = 0;
    int bound_bottom = 0;
    int bound_left = 0;
    int bound_right = 0;
    int vertical_speed_ = 200;
    int horizontal_speed_ = 200;
};