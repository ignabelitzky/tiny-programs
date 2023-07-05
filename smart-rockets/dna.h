#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "params.h"

class DNA {
    public:
        std::vector<sf::Vector2f> genes;

        DNA();
        DNA(std::vector<sf::Vector2f> genes);

        //Copy constructor
        DNA(const DNA& other);

        // Assignment operator
        DNA& operator=(const DNA& other);

        ~DNA();
        sf::Vector2f getGene(int index);
        DNA crossover(DNA partnerDNA);
        void mutation();
};
