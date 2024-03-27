#include "../include/params.hpp"
#include "../include/utils.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    Fluid *fluid = create_fluid(N, 0.0, 0.0, 0.01); // diffusion, viscosity, dt
    sf::RenderWindow window(sf::VideoMode(N, N), "Fluid Simulation");
    sf::View view(sf::FloatRect(0, 0, N, N));
    window.setView(view);
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
                    // Zoom out
                    view.zoom(1.1f);
                }
                window.setView(view);
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            if (position.x < N && position.y < N && position.x > 0 && position.y > 0)
                add_density(fluid, position.x, position.y, 100.0f);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            if (position.x < N && position.y < N && position.x > 0 && position.y > 0)
                add_velocity(fluid, position.x, position.y, 10.0f, 10.0f);
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