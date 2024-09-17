#include "../include/utils.hpp"
#include <random>

int random_int(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

float laplaceA(std::vector<std::vector<std::pair<float, float>>> *grid, int i, int j)
{
    float sumA = 0.0f;
    sumA += grid->at(i).at(j).first * -1;
    sumA += grid->at(i - 1).at(j).first * 0.2;
    sumA += grid->at(i + 1).at(j).first * 0.2;
    sumA += grid->at(i).at(j - 1).first * 0.2;
    sumA += grid->at(i).at(j + 1).first * 0.2;
    sumA += grid->at(i - 1).at(j - 1).first * 0.05;
    sumA += grid->at(i + 1).at(j - 1).first * 0.05;
    sumA += grid->at(i - 1).at(j + 1).first * 0.05;
    sumA += grid->at(i + 1).at(j + 1).first * 0.05;
    return sumA;
}

float laplaceB(std::vector<std::vector<std::pair<float, float>>> *grid, int i, int j)
{
    float sumB = 0.0f;
    sumB += grid->at(i).at(j).second * -1;
    sumB += grid->at(i - 1).at(j).second * 0.2;
    sumB += grid->at(i + 1).at(j).second * 0.2;
    sumB += grid->at(i).at(j - 1).second * 0.2;
    sumB += grid->at(i).at(j + 1).second * 0.2;
    sumB += grid->at(i - 1).at(j - 1).second * 0.05;
    sumB += grid->at(i + 1).at(j - 1).second * 0.05;
    sumB += grid->at(i - 1).at(j + 1).second * 0.05;
    sumB += grid->at(i + 1).at(j + 1).second * 0.05;
    return sumB;
}