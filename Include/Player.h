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
        if ((guy_bounds.top + guy_bounds.height >= wall_bounds.top - 6) && (guy_bounds.top < wall_bounds.top)
            && (guy_bounds.left + guy_bounds.width > wall_bounds.left + 6) && (guy_bounds.left < wall_bounds.left + wall_bounds.width - 6))
        {
            return 1;
        }
        else { return 0; }

    }
    bool Collision_L(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds)
    {
        if ((guy_bounds.left + guy_bounds.width >= wall_bounds.left - 6) && (guy_bounds.left < wall_bounds.left)
            && (guy_bounds.top + guy_bounds.height > wall_bounds.top + 6) && (guy_bounds.top < wall_bounds.top + wall_bounds.height - 6))
        {
            return 1;
        }
        else { return 0; }
    }
    bool Collision_B(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds)
    {
        if ((guy_bounds.top + guy_bounds.height >= wall_bounds.top + 3) && (guy_bounds.top < wall_bounds.top + wall_bounds.height)
            && (guy_bounds.left + guy_bounds.width > wall_bounds.left + 3) && (guy_bounds.left < wall_bounds.left + wall_bounds.width - 3))
        {
            return 1;
        }
        else { return 0; }
    }
    bool Collision_R(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds)
    {
        if ((guy_bounds.left + guy_bounds.width >= wall_bounds.left + 6) && (guy_bounds.left < wall_bounds.left + wall_bounds.width)
            && (guy_bounds.top + guy_bounds.height > wall_bounds.top + 6) && (guy_bounds.top < wall_bounds.top + wall_bounds.height - 6))
        {
            return 1;
        }
        else { return 0; }
    }
    void moveInDirection(const sf::Time& elapsed, const std::vector<sf::Sprite>& obstacles)
    {

        bool top = 0, left = 0, bottom = 0, right = 0;
        for (auto& obstacle : obstacles)
        {
            sf::FloatRect guy_bounds = getGlobalBounds();
            sf::FloatRect wall_bounds = obstacle.getGlobalBounds();
            if (Collision_T(wall_bounds, guy_bounds) == 1) { top = 1; }
            if (Collision_L(wall_bounds, guy_bounds) == 1) { left = 1; }
            if (Collision_B(wall_bounds, guy_bounds) == 1) { bottom = 1; }
            if (Collision_R(wall_bounds, guy_bounds) == 1) { right = 1; }
        }


        sf::FloatRect rectangle_bounds = getGlobalBounds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && bottom != 1) {
            move(0, -std::abs(vertical_speed_ * elapsed.asSeconds()));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && top != 1) {
            move(0, std::abs(vertical_speed_ * elapsed.asSeconds()));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && right != 1) {
            move(-std::abs(horizontal_speed_ * elapsed.asSeconds()), 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && left != 1) {
            move(std::abs(horizontal_speed_ * elapsed.asSeconds()), 0);
        }
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