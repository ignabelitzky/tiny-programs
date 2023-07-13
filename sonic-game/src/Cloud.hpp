#pragma once

#include <SFML/Graphics.hpp>
#include "params.hpp"
#include "helper.hpp"

class Cloud {
    public:
        Cloud(sf::Vector2f position);
        void update(float deltaTime);
        sf::RectangleShape getShape();
        sf::Vector2f getPosition();
    private:
        sf::RectangleShape m_shape;
        sf::Vector2f m_velocity;
        std::vector<sf::Texture> m_textures;
        sf::Texture m_texture;
        void loadTextures();
        float m_cloudVelocity;
};
