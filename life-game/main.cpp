#include <SFML/Graphics.hpp>
#include "params.h"
#include "helper.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game of Life", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    // Calculate the number of rows and columns based on the window size and resolution
    int rows = windowHeight / resolution;
    int cols = windowWidth / resolution;

    // Create the initial grid and populate it with random values
    int** grid = make2DArray(rows, cols);
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            grid[i][j] = genRandomInt(0, 1);
        }
    }

    // Create the next grid and a temporary grid for swapping
    int** next = make2DArray(rows, cols);
    int** tmp;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            } else if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }
        window.clear();

        // Draw the cells based on the grid values
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                int x = j * resolution;
                int y = i * resolution;
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(resolution-1, resolution-1));
                rect.setPosition(x, y);
                if(grid[i][j] == 1) {
                    rect.setFillColor(sf::Color::White);
                } else {
                    rect.setFillColor(sf::Color::Black);
                }
                window.draw(rect);
            }
        }

        // Update the grid based on the Game of Life rules
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                int neighbors = countNeighbors(grid, i, j, rows);
                int state = grid[i][j];
                if(state == 0 && neighbors == 3) {
                    next[i][j] = 1;
                } else if(state == 1 && (neighbors < 2 || neighbors > 3)) {
                    next[i][j] = 0;
                } else {
                    next[i][j] = state;
                }
            }
        }

        // swap the grid by using a temporary variable
        tmp = grid;
        grid = next;
        next = tmp;

        window.display();
    }

    // Cleanup: Deallocate memory for the grids
    delete2DArray(grid, rows);
    delete2DArray(next, rows);

    return 0;
}
