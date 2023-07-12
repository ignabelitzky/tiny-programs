#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include "params.hpp"

class Floor {
    public:
        Floor();
        void update(float dt);
        std::vector<sf::Sprite> getSprites();
    private:
        std::vector<sf::Sprite> m_floorSprites;
        sf::Texture m_texture;
        void loadTexture();
};
