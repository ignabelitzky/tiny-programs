#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "params.h"
#include "dna.h"

class Rocket {
    public:
        Rocket();
        Rocket(DNA d);
        ~Rocket();
        void applyForce(sf::Vector2f force);
        void calcFitness(sf::Vector2f targetPos);
        void update(sf::Vector2f targetPos);
        void show(sf::RenderWindow& window);
        DNA getDNA();
        float getFitness();
        void setFitness(float f);
    private:
        sf::RectangleShape m_rocket;
        sf::Vector2f m_position;
        sf::Vector2f m_velocity;
        sf::Vector2f m_acceleration;
        float m_rotationAngle;
        float m_fitness;
        DNA m_dna;
        bool m_completed;
};
