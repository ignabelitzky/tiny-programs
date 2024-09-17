#include "../include/params.hpp"
#include "../include/utils.hpp"
#include <omp.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <algorithm>

int main()
{
    // Create two grids
    std::vector<std::vector<std::pair<float, float>>> gridOne(params::width, std::vector<std::pair<float, float>>(params::height));
    std::vector<std::vector<std::pair<float, float>>> gridTwo(params::width, std::vector<std::pair<float, float>>(params::height));
    
    std::vector<std::vector<std::pair<float, float>>>* currentGrid = &gridOne;
    std::vector<std::vector<std::pair<float, float>>>* nextGrid = &gridTwo;

    // Initialize the grids
    #pragma omp parallel for collapse(2) schedule(static)
    for (int i = 0; i < params::width; i++)
    {
        for (int j = 0; j < params::height; j++)
        {
            (*currentGrid)[i][j] = std::make_pair(1.0f, 0.0f);
            (*nextGrid)[i][j] = std::make_pair(1.0f, 0.0f);
        }
    }

    // Create a pattern in the grid
    #pragma omp parallel for collapse(2) schedule(static)
    for (int i = 100; i < 150; ++i)
    {
        for (int j = 100; j < 150; ++j)
        {
            if (i < params::width && j < params::height) // Bounds checking
            {
                (*currentGrid)[i][j] = std::make_pair(0.0f, 1.0f);
            }
        }
    }

    #pragma omp parallel for collapse(2) schedule(static)
    for (int i = 500; i < 550; ++i)
    {
        for (int j = 500; j < 550; ++j)
        {
            if (i < params::width && j < params::height) // Bounds checking
            {
                (*currentGrid)[i][j] = std::make_pair(0.0f, 1.0f);
            }
        }
    }

    // Create the window
    sf::RenderWindow window(sf::VideoMode(params::width, params::height), "SFML works!");

    // Create an sf::Image
    sf::Image image;
    image.create(params::width, params::height, sf::Color::White);

    // Create a texture from the image
    sf::Texture texture;
    texture.loadFromImage(image);

    // Create a sprite to display the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen())
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.clear();

    // Update the grid values
    #pragma omp parallel for collapse(2) schedule(static)
    for (int i = 1; i < params::width - 1; i++)
    {
        for (int j = 1; j < params::height - 1; j++)
        {
            float a = currentGrid->at(i).at(j).first;
            float b = currentGrid->at(i).at(j).second;
            nextGrid->at(i).at(j).first = a + params::dA * laplaceA(currentGrid, i, j) - a * b * b + params::feed * (1 - a);
            nextGrid->at(i).at(j).second = b + params::dB * laplaceB(currentGrid, i, j) + a * b * b - (params::kill + params::feed) * b;
        }
    }

    // Update the image based on the grid
    #pragma omp parallel for collapse(2) schedule(static)
    for (int i = 0; i < params::width; i++)
    {
        for (int j = 0; j < params::height; j++)
        {
            sf::Uint8 red = static_cast<sf::Uint8>(std::clamp(currentGrid->at(i).at(j).first * 255.0f, 0.0f, 255.0f));
            sf::Uint8 blue = static_cast<sf::Uint8>(std::clamp(currentGrid->at(i).at(j).second * 255.0f, 0.0f, 255.0f));
            image.setPixel(i, j, sf::Color(red, 0, blue, 255));
        }
    }

    texture.update(image); // Update the texture with the new image data
    window.draw(sprite);
    window.display();

    std::swap(currentGrid, nextGrid); // Swap the grids
}

    return 0;
}