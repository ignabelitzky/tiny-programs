#include "../include/params.hpp"
#include "../include/utils.hpp"
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    Fluid *fluid = create_fluid(N, 0.0, 0.0, 0.07); // diffusion, viscosity, dt
    sf::RenderWindow window(sf::VideoMode(N, N), "Fluid Simulation");
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    window.setSize(sf::Vector2u(desktopMode.width, desktopMode.height));
    sf::View view(sf::FloatRect(0, 0, N, N));
    window.setView(view);

    bool isPanning = false;
    sf::Vector2i lastMousePos;

    for (int i = 0; i < 20000; i++)
    {
        add_density(fluid, rand() % (N - 2), rand() % (N - 2), rand() % 300 + 50);
    }

    for (int i = 0; i < 5000; i++)
    {
        float value1 = (float)rand() / RAND_MAX * 2.0f - 1.0f;
        float value2 = (float)rand() / RAND_MAX * 2.0f - 1.0f;
        add_velocity(fluid, rand() % (N - 80) + 40, rand() % (N - 80) + 40, value1, value2);
    }

    for (int i = 0; i < 20000; i++)
    {
        add_density(fluid, rand() % (N - 2), rand() % (N - 2), rand() % 300 + 50);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0)
                {
                    // Zoom in
                    view.zoom(0.9f);
                }
                else if (event.mouseWheelScroll.delta < 0)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f viewCenter = window.mapPixelToCoords(mousePos, view);
                    if (view.getSize().x > window.getSize().x && view.getSize().y > window.getSize().y)
                    {
                        view.zoom(1.1f);
                    }
                    else
                    {
                        view.setSize(window.getSize().x, window.getSize().y);
                        view.setCenter(viewCenter);
                    }
                }
                window.setView(view);
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle)
            {
                isPanning = true;
                lastMousePos = sf::Mouse::getPosition(window);
            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Middle)
            {
                isPanning = false;
            }
            else if (event.type == sf::Event::MouseMoved && isPanning)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f offset =
                    window.mapPixelToCoords(lastMousePos, view) - window.mapPixelToCoords(mousePos, view);
                view.move(offset);
                window.setView(view);
                lastMousePos = mousePos;
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                for (int i = 0; i < 1000; i++)
                {
                    add_density(fluid, rand() % (N - 2), rand() % (N - 2), rand() % 300 + 50make);
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                for (int i = 0; i < 100; i++)
                {
                    float value1 = (float)rand() / RAND_MAX * 2.0f - 1.0f;
                    float value2 = (float)rand() / RAND_MAX * 2.0f - 1.0f;
                    add_velocity(fluid, rand() % (N - 80) + 40, rand() % (N - 80) + 40, value1, value2);
                }
            }
        }
        step(fluid, N);
        sf::Uint8 *pixels = new sf::Uint8[N * N * 4];
        for (int i = 1; i < N - 1; i++)
        {
            for (int j = 1; j < N - 1; j++)
            {
                int index = 4 * (i + j * N);
                float d = fluid->density[IX(i, j, N)];
                pixels[index] = d;     // R
                pixels[index + 1] = d; // G
                pixels[index + 2] = d; // B
                pixels[index + 3] = 255;
            }
        }
        sf::Texture texture;
        texture.create(N, N);
        texture.update(pixels);
        delete[] pixels;
        sf::Sprite sprite(texture);
        window.clear();
        window.draw(sprite);
        window.display();
    }

    free_fluid(fluid);

    return 0;
}