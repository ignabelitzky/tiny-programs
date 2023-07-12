#pragma once

#include<SFML/Graphics.hpp>

class Sonic {
    public:
        Sonic(sf::Vector2f position, float groundLevel, float skyLevel);

        void update(float deltaTime);
        void jump();
        sf::RectangleShape getShape();
    private:
        sf::RectangleShape m_shape;
        sf::Vector2f m_velocity;
        bool m_isJumping;
        float m_jumpSpeed;
        float m_groundLevel;
        float m_skyLevel;
        float m_bounceFactor;
};
