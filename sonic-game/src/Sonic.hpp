#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Sonic {
    public:
        Sonic(sf::Vector2f position, float groundLevel, float skyLevel);

        void update(float deltaTime);
        void jump();
        sf::RectangleShape getShape();
        sf::Sprite getSprite();
        void applyNextRunSprite();

    private:
        sf::RectangleShape m_shape;
        sf::Sprite m_sprite;
        sf::Vector2f m_velocity;
        bool m_isJumping;
        float m_jumpSpeed;
        float m_groundLevel;
        float m_skyLevel;
        float m_bounceFactor;
        std::vector<sf::Texture> m_runTextures;
        size_t m_runIndex;
        std::vector<sf::Texture> m_jumpTextures;
};
