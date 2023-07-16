#pragma once

#include <SFML/Graphics.hpp>
#include "params.h"

class Helicopter {
    public:
        Helicopter(int width, int height, sf::Vector2f position);
        void up();
        void update();
        void show(sf::RenderWindow& window);
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        bool isAlive();
        void revive();
    private:
        sf::RectangleShape m_helicopter;
        sf::Texture m_texture;
        sf::Vector2u m_textureSize;
        int m_textureWidth;
        int m_textureHeight;
        sf::IntRect m_textureRect;
        sf::Vector2f m_position;
        float m_gravity;
        float m_upForce;
        sf::Vector2f m_velocity;
        bool m_isAlive;
        sf::Clock m_clock;
        float m_elapsedTime;
        float m_frameDuration;
};
