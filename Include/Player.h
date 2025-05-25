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


    bool Collision_T(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds)
    {
        if ((guy_bounds.top + guy_bounds.height >= wall_bounds.top - 1) && (guy_bounds.top < wall_bounds.top)
            && (guy_bounds.left + guy_bounds.width > wall_bounds.left + 3) && (guy_bounds.left < wall_bounds.left + wall_bounds.width - 3))
        {
            return 1;
        }
        else { return 0; }

    }
    bool Collision_L(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds)
    {
        if ((guy_bounds.left + guy_bounds.width >= wall_bounds.left - 1) && (guy_bounds.left < wall_bounds.left)
            && (guy_bounds.top + guy_bounds.height > wall_bounds.top + 3) && (guy_bounds.top < wall_bounds.top + wall_bounds.height - 3))
        {
            return 1;
        }
        else { return 0; }
    }
    bool Collision_B(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds)
    {
        if ((guy_bounds.top + guy_bounds.height >= wall_bounds.top + 1) && (guy_bounds.top < wall_bounds.top + wall_bounds.height)
            && (guy_bounds.left + guy_bounds.width > wall_bounds.left + 3) && (guy_bounds.left < wall_bounds.left + wall_bounds.width - 3))
        {
            return 1;
        }
        else { return 0; }
    }
    bool Collision_R(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds)
    {
        if ((guy_bounds.left + guy_bounds.width >= wall_bounds.left + 1) && (guy_bounds.left < wall_bounds.left + wall_bounds.width)
            && (guy_bounds.top + guy_bounds.height > wall_bounds.top + 3) && (guy_bounds.top < wall_bounds.top + wall_bounds.height - 6))
        {
            return 1;
        }
        else { return 0; }
    }
    void resolveCollisionWithWalls(const std::vector<sf::Sprite>& obstacles, float move_x, float move_y)
    {
        // --- Move X
        move(move_x, 0);
        for (const auto& wall : obstacles)
        {
            if (getGlobalBounds().intersects(wall.getGlobalBounds()))
            {
                auto playerBounds = getGlobalBounds();
                auto wallBounds = wall.getGlobalBounds();

                if (move_x > 0) // moving right
                {
                    float overlap = (playerBounds.left + playerBounds.width) - wallBounds.left;
                    move(-overlap, 0);
                }
                else if (move_x < 0) // moving left
                {
                    float overlap = (wallBounds.left + wallBounds.width) - playerBounds.left;
                    move(overlap, 0);
                }
            }
        }

        // --- Move Y
        move(0, move_y);
        for (const auto& wall : obstacles)
        {
            if (getGlobalBounds().intersects(wall.getGlobalBounds()))
            {
                auto playerBounds = getGlobalBounds();
                auto wallBounds = wall.getGlobalBounds();

                if (move_y > 0) // moving down
                {
                    float overlap = (playerBounds.top + playerBounds.height) - wallBounds.top;
                    move(0, -overlap);
                }
                else if (move_y < 0) // moving up
                {
                    float overlap = (wallBounds.top + wallBounds.height) - playerBounds.top;
                    move(0, overlap);
                }
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


private:
    int m_speed_x = 200;
    int m_speed_y = 200;
    int bound_top = 0;
    int bound_bottom = 0;
    int bound_left = 0;
    int bound_right = 0;
    int vertical_speed_ = 200;
    int horizontal_speed_ = 200;
};