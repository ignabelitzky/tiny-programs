#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "params.hpp"

class Crab {
    public:
        Crab(sf::Vector2f position);
        void update(float deltaTime);
        sf::CircleShape getShape();
        sf::Vector2f getPosition();
        float getRadius();
        bool isPassed();
        void setPassed(bool value);
    private:
        sf::CircleShape m_shape;
        sf::Vector2f m_velocity;
        std::vector<sf::Texture> m_textures;
        size_t m_textureIndex;
        bool m_passed;
        void loadTextures();
        sf::Clock m_clock;
        sf::Time m_elapsed;
        sf::Time m_frameDuration;
};
