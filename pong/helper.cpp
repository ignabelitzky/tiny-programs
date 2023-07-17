#include "helper.hpp"

float getRandomFloat(float min, float max) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::default_random_engine generator(std::rand());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}
