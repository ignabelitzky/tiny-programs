#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <utility>

int random_int(int min, int max);

float laplaceA(std::vector<std::vector<std::pair<float, float>>> *grid, int i, int j);

float laplaceB(std::vector<std::vector<std::pair<float, float>>> *grid, int i, int j);

#endif