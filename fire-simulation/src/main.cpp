#include "../include/params.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <omp.h>

struct color
{
    int r;
    int g;
    int b;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Fire Simulation");
    sf::Texture texture;
    texture.create(width, height);
    sf::Uint8 *bufferPixels1 = new sf::Uint8[width * height * 4];
    sf::Uint8 *bufferPixels2 = new sf::Uint8[width * height * 4];
    std::fill_n(bufferPixels1, width * height * 4, 0); // Set all bufferPixels1 to black
    std::fill_n(bufferPixels2, width * height * 4, 0); // Set all bufferPixels2 to black
    for (int x = 1; x < width - 1; ++x)
    {
        for (int y = height - 50; y < height - 1; ++y)
        {
            int index = x + y * width;
            bufferPixels1[index * 4] = 255;     // Set red channel to 255
            bufferPixels1[index * 4 + 1] = 255; // Set green channel to 255
            bufferPixels1[index * 4 + 2] = 255; // Set blue channel to 255
            bufferPixels1[index * 4 + 3] = 255; // Set alpha channel to 255
        }
    }
    texture.update(bufferPixels1);
    sf::Sprite sprite(texture);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
#pragma omp parallel for collapse(2)
        for (int x = 1; x < width - 1; ++x)
        {
            for (int y = 1; y < height - 1; ++y)
            {
                int index = (x + (y - 1) * width) * 4;
                int index1 = ((x + 1) + y * width) * 4;
                int index2 = ((x - 1) + y * width) * 4;
                int index3 = (x + (y + 1) * width) * 4;
                int index4 = (x + (y - 1) * width) * 4;
                struct color c1 = {bufferPixels1[index1], bufferPixels1[index1 + 1], bufferPixels1[index1 + 2]};
                struct color c2 = {bufferPixels1[index2], bufferPixels1[index2 + 1], bufferPixels1[index2 + 2]};
                struct color c3 = {bufferPixels1[index3], bufferPixels1[index3 + 1], bufferPixels1[index3 + 2]};
                struct color c4 = {bufferPixels1[index4], bufferPixels1[index4 + 1], bufferPixels1[index4 + 2]};
                struct color newColor = {c1.r + c2.r + c3.r + c4.r, c1.g + c2.g + c3.g + c4.g,
                                         c1.b + c2.b + c3.b + c4.b};
                bufferPixels2[index] = newColor.r / 4;
                bufferPixels2[index + 1] = newColor.g / 4;
                bufferPixels2[index + 2] = newColor.b / 4;
            }
        }
        texture.update(bufferPixels2);
        window.draw(sprite);
        window.display();
        sf::Uint8 *temp = bufferPixels1;
        bufferPixels1 = bufferPixels2;
        bufferPixels2 = temp;
    }
    return 0;
}
