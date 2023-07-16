#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "params.hpp"

enum Lane {
    LEFT,
    CENTER,
    RIGHT
};

class Car {
    public:
        Car();
        ~Car();
        void loadTexture(const std::string& textureFile);
        void setPosition(float x, float y);
        void moveLeft();
        void moveRight();
        void draw(sf::RenderWindow& window);
    private:
        Lane incrementLane(Lane lane);
        Lane decrementLane(Lane lane);
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Vector2f m_position;
        float m_speed;
        Lane m_lane;
};
