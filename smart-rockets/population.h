#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "rocket.h"

class Population {
    public:
        Population(int size);
        ~Population();
        void evaluate(sf::Vector2f targetPos);
        void selection();
        void run(sf::RenderWindow& window, sf::Vector2f targetPos);
        int size();
    private:
        std::vector<Rocket> m_rockets;
        std::vector<Rocket> m_matingPool;
};
