#include "helper.h"

float genRandomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(gen);
}

int genRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

sf::Vector2f genRandomVector(float min, float max) {
    return sf::Vector2f(genRandomFloat(min, max), genRandomFloat(min, max));
}
