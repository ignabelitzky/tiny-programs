#include "helper.h"

int** make2DArray(int rows, int cols) {
    int** matrix = new int*[rows];
    #pragma omp parallel for
    for(int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void delete2DArray(int** matrix, int rows) {
    #pragma omp parallel for
    for(int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int genRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

int countNeighbors(int** grid, int x, int y, int gridSize) {
    int sum = 0;
    #pragma omp parallel for collapse(2) reduction(+:sum)
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            // Handle wrap-around for cells on the edges of the grid
            int neighborX = (x + i + gridSize) % gridSize;
            int neighborY = (y + j + gridSize) % gridSize;
            sum += grid[neighborX][neighborY];
        }
    }
    sum -= grid[x][y];
    return sum;
}
