#pragma once

#include <SFML/Graphics.hpp>

class Ball {
    public:
        Ball(int radius, sf::Vector2f position, sf::Vector2f velocity);
        ~Ball();
        void update();
        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f position);
        void setVelocity(sf::Vector2f velocity);
        sf::Vector2f getVelocity();
        void render(sf::RenderWindow& window);
    private:
        int m_radius;
        sf::CircleShape m_ball;
        sf::Vector2f m_position;
        sf::Vector2f m_velocity;
};
