#include "../include/utils.hpp"
#include <random>

int random_int(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

template <typename T>
T laplace(const std::vector<std::vector<std::pair<float, float>>> *grid, int i, int j, bool isA)
{
    const int rows = grid->size();
    const int cols = grid->at(0).size();

    // Ensure indices are within bounds
    if (i < 0 || i >= rows || j < 0 || j >= cols)
    {
        return 0.0f;
    }

    T sum = 0.0f;
    const T& center = isA ? grid->at(i).at(j).first : grid->at(i).at(j).second;

    sum += center * -1;
    sum += (isA ? grid->at(i - 1).at(j).first : grid->at(i - 1).at(j).second) * 0.2;
    sum += (isA ? grid->at(i + 1).at(j).first : grid->at(i + 1).at(j).second) * 0.2;
    sum += (isA ? grid->at(i).at(j - 1).first : grid->at(i).at(j - 1).second) * 0.2;
    sum += (isA ? grid->at(i).at(j + 1).first : grid->at(i).at(j + 1).second) * 0.2;
    sum += (isA ? grid->at(i - 1).at(j - 1).first : grid->at(i - 1).at(j - 1).second) * 0.05;
    sum += (isA ? grid->at(i + 1).at(j - 1).first : grid->at(i + 1).at(j - 1).second) * 0.05;
    sum += (isA ? grid->at(i - 1).at(j + 1).first : grid->at(i - 1).at(j + 1).second) * 0.05;
    sum += (isA ? grid->at(i + 1).at(j + 1).first : grid->at(i + 1).at(j + 1).second) * 0.05;

    return sum;
}

float laplaceA(std::vector<std::vector<std::pair<float, float>>> *grid, int i, int j)
{
    return laplace<float>(grid, i, j, true);
}

float laplaceB(std::vector<std::vector<std::pair<float, float>>> *grid, int i, int j)
{
    return laplace<float>(grid, i, j, false);
}