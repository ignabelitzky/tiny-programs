#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "utils.hpp"
#include <SFML/Graphics.hpp>

class Circle
{
  public:
    Circle();
    Circle(int radius, sf::Color color, sf::Vector2f position);
    void draw(sf::RenderWindow &window);
    void update(float deltaTime);
    void update_without_gravity(float deltaTime);

    const sf::CircleShape get_shape() const
    {
        return shape;
    }
    const sf::Vector2f get_position() const
    {
        return position;
    }
    const sf::Vector2f get_velocity() const
    {
        return velocity;
    }
    void set_position(sf::Vector2f position)
    {
        this->position = position;
    }
    void set_velocity(sf::Vector2f velocity)
    {
        this->velocity = velocity;
    }

  private:
    sf::Color color;
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
};

#endif
