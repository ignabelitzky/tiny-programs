#include "helper.hpp"

float getRandomFloat(float min, float max) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::default_random_engine generator(std::rand());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}

void saveMaxScore(int maxScore) {
    std::ofstream file("maxscore.txt");
    if(file.is_open()) {
        file << maxScore;
        file.close();
        std::cout << "Max score saved successfully.\n";
    } else {
        std::cout << "Error openening the maxscore file.\n";
    }
}

int retrieveMaxScore() {
    std::ifstream file("maxscore.txt");
    int maxScore = 0;
    if(file.is_open()) {
        file >> maxScore;
        file.close();
        std::cout << "Max score retrieved successfully.\n";
    } else {
        std::cout << "Error opening the maxscore file.\n";
    }
    return maxScore;
}
