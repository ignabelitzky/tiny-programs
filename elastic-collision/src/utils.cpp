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

std::pair<float, float> utils::normalize(const std::pair<float, float> &v)
{
    float mag = std::sqrt(std::pow(v.first, 2) + std::pow(v.second, 2));
    if (mag > 0.0f)
    {
        return std::make_pair(v.first / mag, v.second / mag);
    }
    else
    {
        return std::make_pair(0.0f, 0.0f);
    }
}

std::pair<float, float> utils::setMagnitude(std::pair<float, float> v, float mag)
{
    std::pair<float, float> unitVec = utils::normalize(v);
    return std::make_pair(unitVec.first * mag, unitVec.second * mag);
}