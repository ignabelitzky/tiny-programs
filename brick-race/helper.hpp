#pragma once

#include <iostream>
#include <random>
#include <fstream>
#include "params.hpp"

template<typename T>
T getRandomNumber(T min, T max);

void saveHighScore(const int highScore, const std::string& fileName);

int loadHighScore(const std::string& fileName);
