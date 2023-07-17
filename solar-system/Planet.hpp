#pragma once

#include <SFML/Graphics.hpp>
#include "params.hpp"
#include "helper.hpp"

class Planet {
    public:
        Planet(float radius, float distance, float orbitSpeed = 0.f);
        ~Planet();
        sf::CircleShape getShape();
        sf::Vector2f getPosition();
        void setPosition(float x, float y);
        void setFillColor(sf::Color color);
        void setOrigin(float x, float y);
        float getDistance();
        void setAngle(float angle);
        float getAngle();
        void spawnMoons(int total);
        std::vector<Planet> getMoons();
        void orbit();
        void update();
    private:
        float m_radius;
        float m_angle;
        float m_distance;
        float m_orbitSpeed;
        sf::CircleShape m_shape;
        std::vector<Planet> m_moons;
};
