#include "helper.h"

float getRandomFloat(float min, float max) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::default_random_engine generator(std::rand());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}

int getRandomInt(int min, int max) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::default_random_engine generator(std::rand());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}
