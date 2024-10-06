#ifndef WALKER_HPP
#define WALKER_HPP

#include <utility>
#include <SFML/Graphics.hpp>

class Walker
{
public:
    Walker();
    std::pair<int, int> getPosition();
    void setPosition(int x, int y);
    sf::Color getColor();
    void setColor(sf::Color color);
    void display(sf::RenderWindow &window);
    void step();

private:
    sf::CircleShape shape;
    sf::Color color;
    int radius;
    std::pair<int, int> position;
};

#endif