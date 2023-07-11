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

void saveMaxScore(int maxScore) {
    std::ofstream file("maxscore.txt");
    if(file.is_open()) {
        file << maxScore;
        file.close();
        std::cout << "Max score saved successfully." << std::endl;
    } else {
        std::cout << "Error openening file." << std::endl;
    }
}

int retrieveMaxScore() {
    std::ifstream file("maxscore.txt");
    int maxScore = 0;
    if(file.is_open()) {
        file >> maxScore;
        file.close();
        std::cout << "Max score retrieved successfully." << std::endl;
    } else {
        std::cout << "Error openening file." << std::endl;
    }
    return maxScore;
}
