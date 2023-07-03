#pragma once

#include <SFML/Graphics.hpp>

class Boundary {
    public:
        Boundary(float x1, float y1, float x2, float y2);
        ~Boundary();
        void show(sf::RenderWindow& window);
        sf::Vector2f getFstPoint();
        sf::Vector2f getSndPoint();
    private:
        sf::Vector2f fstPoint;
        sf::Vector2f sndPoint;
};
