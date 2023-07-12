#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "params.hpp"

class Enemy {
    public:
        Enemy(sf::Vector2f position);
        void update(float deltaTime);
        sf::CircleShape getShape();
    private:
        sf::CircleShape m_shape;
        sf::Vector2f m_velocity;
        std::vector<sf::Texture> m_textures;
        size_t m_textureIndex;
        void loadTextures();
        sf::Clock m_clock;
        sf::Time m_elapsed;
        sf::Time m_frameDuration;
};
