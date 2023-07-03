#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cmath>
#include <limits>
#include <optional>
#include "params.h"
#include "ray.h"
#include "boundary.h"

class Particle {
    public:
        Particle();
        ~Particle();
        void show(sf::RenderWindow& window);
        void look(sf::RenderWindow& window, std::vector<Boundary> boundaries);
        void update(float x, float y);
    private:
        sf::Vector2f position;
        std::vector<Ray> rays;
};
