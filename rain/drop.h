#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "params.h"

class Drop {
    public:
        Drop();
        ~Drop();
        void fall();
        void show(sf::RenderWindow& window);
        sf::Vector2f getPosition();
        void setPosition(float x, float y);
    private:
        sf::Vector2f position;
        float ySpeed;
};
