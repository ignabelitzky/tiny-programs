#include "../include/walker.hpp"
#include "../include/params.hpp"
#include "../include/utils.hpp"

Walker::Walker()
{
    position = std::make_pair(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    int radius = 3;
    color = sf::Color::White;
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(position.first, position.second);
}

std::pair<int, int> Walker::getPosition()
{
    return this->position;
}

void Walker::setPosition(int x, int y)
{
    this->position = std::make_pair(x, y);
}

sf::Color Walker::getColor()
{
    return color;
}

void Walker::setColor(sf::Color color)
{
    this->color = color;
    shape.setFillColor(color);
}

void Walker::display(sf::RenderWindow &window)
{
    this->shape.setPosition(this->position.first, this->position.second);
    window.draw(this->shape);
}

void Walker::step()
{
    int choice = random_int(1, 4);
    switch (choice)
    {
        case 1:
            this->position.first++;
            break;
        case 2:
            this->position.first--;
            break;
        case 3:
            this->position.second++;
            break;
        case 4:
            this->position.second--;
            break;
        default:
            break;
    }

    this->position.first = std::max(0, std::min(WINDOW_WIDTH, position.first));
    this->position.second = std::max(0, std::min(WINDOW_HEIGHT, position.second));
    
    this->color = sf::Color(random_int(0, 255), random_int(0, 255), random_int(0, 255));
    this->shape.setFillColor(this->color);
}