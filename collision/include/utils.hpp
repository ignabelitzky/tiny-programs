#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <SFML/Graphics.hpp>
#include <random>

namespace utils
{
    float random(float min, float max);
    sf::Color randomColor();
}

#endif