#include "../include/utils.hpp"

float utils::random(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

sf::Color utils::randomColor()
{
    return sf::Color(utils::random(0, 255), utils::random(0, 255), utils::random(0, 255));
}