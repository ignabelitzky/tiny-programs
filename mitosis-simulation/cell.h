#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "helper.h"

class Cell {
    public:
        Cell(sf::Vector2f position, float radius);
        Cell(sf::Vector2f position, float radius, sf::Color color);
        ~Cell();
        void show(sf::RenderWindow& window);
        void move();
        bool mousePressed(sf::Vector2i clickPosition);
        Cell mitosis();
    private:
        sf::CircleShape m_cell;
        sf::Color m_color;
        sf::Vector2f m_position;
        sf::Vector2f m_velocity;
        float m_acceleration;
        float m_radius;
};
