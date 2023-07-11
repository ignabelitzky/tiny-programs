#pragma once

#include <SFML/Graphics.hpp>
#include "params.h"

class Helicopter {
    public:
        Helicopter(int radius, sf::Vector2f position);
        ~Helicopter();
        void up();
        void update();
        void show(sf::RenderWindow& window);
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        bool isAlive();
        void revive();
    private:
        sf::CircleShape m_helicopter;
        sf::Texture m_texture;
        sf::Vector2f m_position;
        int m_radius;
        float m_gravity;
        float m_upForce;
        sf::Vector2f m_velocity;
        bool m_isAlive;
};
