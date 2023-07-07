#pragma once

#include <SFML/Graphics.hpp>
#include <random>

int** make2DArray(int cols, int rows);

void delete2DArray(int** matrix, int rows);

int genRandomInt(int min, int max);

int countNeighbors(int** grid, int x, int y, int gridSize);
