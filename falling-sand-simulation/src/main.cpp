#include "../include/params.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), PROJECT_NAME, sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    int rows = WINDOW_HEIGHT / CELL_SIZE;
    int cols = WINDOW_WIDTH / CELL_SIZE;

    // Create the grid
    int **grid = new int *[rows];
    for (int i = 0; i < rows; ++i)
    {
        grid[i] = new int[cols];
    }

    // Fill the grid with 0's
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            grid[i][j] = 0;
        }
    }

    grid[2][2] = 1;

    sf::Clock clock;
    sf::Time interval = sf::seconds(0.2f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        if (clock.getElapsedTime() >= interval)
        {
            window.clear();

            // Draw the cells based on the grid values
            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < cols; ++j)
                {
                    int x = j * CELL_SIZE;
                    int y = i * CELL_SIZE;

                    sf::RectangleShape rect;
                    rect.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                    rect.setPosition(x, y);
                    if (grid[i][j] == 1)
                    {
                        rect.setFillColor(sf::Color::White);
                    }
                    else
                    {
                        rect.setFillColor(sf::Color::Black);
                    }
                    window.draw(rect);
                }
            }

            bool updated = false;

            for (int i = 0; i < rows - 1; ++i)
            {
                for (int j = 0; j < cols; ++j)
                {
                    if (grid[i][j] == 1 && !updated)
                    {
                        grid[i][j] = 0;
                        grid[i + 1][j] = 1;
                        updated = true;
                    }
                }
            }

            window.display();

            clock.restart();
        }
    }

    // Delete the grid
    for (int i = 0; i < rows; ++i)
    {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}
