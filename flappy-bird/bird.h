#pragma once

#include <SFML/Graphics.hpp>
#include "params.h"

class Bird {
    public:
        Bird(int radius, sf::Vector2f position);
        ~Bird();
        void up();
        void update();
        void show(sf::RenderWindow& window);
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
    private:
        sf::CircleShape m_bird;
        sf::Color m_color;
        sf::Vector2f m_position;
        int m_radius;
        float m_gravity;
        float m_upForce;
        sf::Vector2f m_velocity;
        bool m_isAlive;
};
