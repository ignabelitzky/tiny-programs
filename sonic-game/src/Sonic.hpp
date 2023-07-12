#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Sonic {
    public:
        Sonic(sf::Vector2f position, float groundLevel, float skyLevel);

        void update(float deltaTime);
        void jump();
        sf::CircleShape getShape();

    private:
        sf::CircleShape m_shape;
        sf::Vector2f m_velocity;
        bool m_isJumping;
        float m_jumpSpeed;
        float m_groundLevel;
        float m_skyLevel;
        float m_bounceFactor;
        std::vector<sf::Texture> m_runTextures;
        size_t m_runIndex;
        std::vector<sf::Texture> m_jumpTextures;
        sf::Clock m_clock;
        sf::Time m_elapsed;
        sf::Time m_frameDuration;
};
