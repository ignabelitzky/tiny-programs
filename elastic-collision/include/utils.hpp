#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <SFML/Graphics.hpp>
#include <random>

namespace utils
{
    float random(float min, float max);
    sf::Color randomColor();
    std::pair<float, float> normalize(const std::pair<float, float> &v);
    std::pair<float, float> setMagnitude(std::pair<float, float> v, float mag);
}

#endif