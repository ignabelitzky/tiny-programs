#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "helper.h"

class Particle {
    public:
        Particle(sf::Vector2f position, float radius);
        ~Particle();
        void update();
        void show(sf::RenderWindow& window);
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        void setVelocity(sf::Vector2f velocity);
        sf::Vector2f getVelocity();
        void setColor(sf::Color color);
    private:
        sf::CircleShape m_particle;
        float m_radius;
        sf::Vector2f m_position;
        sf::Vector2f m_velocity;
        sf::Color m_color;
};

class Splash {
    public:
        Splash(sf::Vector2f position);
        ~Splash();
        void update();
        void show(sf::RenderWindow& window);
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
    private:
        sf::Vector2f m_position;
        std::vector<Particle> m_drops;
};
