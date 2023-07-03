#pragma once

#include <cmath>
#include <optional>
#include <SFML/Graphics.hpp>
#include "boundary.h"

class Ray {
    public:
        Ray(sf::Vector2f pos, float angle);
        ~Ray();
        void show(sf::RenderWindow& window);
        std::optional<sf::Vector2f> cast(Boundary b);
        void setPosition(float posX, float posY);
        void setDirection(float dirX, float dirY);
        sf::Vector2f getPosition();
        sf::Vector2f getDirection();
    private:
        void normalizeDirection();
        sf::Vector2f position;
        sf::Vector2f direction;
};
