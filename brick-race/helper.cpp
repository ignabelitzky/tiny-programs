#include "helper.hpp"

template<typename T>
T getRandomNumber(T min, T max) {
    std::random_device rd;
    std::mt19937 generator(rd());
    if constexpr(std::is_integral<T>::value) {
        std::uniform_int_distribution<T> distribution(min, max);
        return distribution(generator);
    } else if constexpr(std::is_floating_point<T>::value) {
        std::uniform_real_distribution<T> distribution(min, max);
        return distribution(generator);
    }

    // Return default value if T is neither integral nor floating-point
    return T{};
}

void saveHighScore(const int highScore, const std::string& fileName) {
    std::string highScoreFile = HIGHSCORE_DIR + fileName;
    std::ofstream file(highScoreFile);
    if(!file.is_open()) {
        std::cout << "Error: Highscore file cannot be opened.\n";
        return;
    }
    file << highScore;
    file.close();
}

int loadHighScore(const std::string& fileName) {
    int highScore = 0;
    std::string highScoreFile = HIGHSCORE_DIR + fileName;
    std::ifstream file(highScoreFile);
    if(!file.is_open()) {
        std::cout << "Error: Highscore file cannot be opened.\n";
        return highScore;
    }
    file >> highScore;
    file.close();

    return highScore;
}
