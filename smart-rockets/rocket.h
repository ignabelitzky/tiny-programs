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
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        float rotationAngle;
        float fitness;
        DNA dna;
        bool completed;
        bool crashed;
};
