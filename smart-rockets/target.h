#pragma once

#include <SFML/Graphics.hpp>
#include "params.h"

class Target {
    public:
        Target(sf::Vector2f position, float radius);
        ~Target();
        void update();
        void show(sf::RenderWindow& window);
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        void setRadius(float radius);
        float getRadius();
    private:
        sf::CircleShape m_target;
        sf::Vector2f m_position;
        float m_radius;
        sf::Texture m_texture;
};
