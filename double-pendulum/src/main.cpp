#include "../include/pendulum.hpp"

int main()
{
    Pendulum pendulum;

    sf::RenderWindow window(sf::VideoMode(width, height), "Double Pendulum Simulation");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::R)
                {
                    pendulum.reset();
                }
            }
        }

        window.clear(sf::Color::White);
        pendulum.update(0.01f);
        pendulum.draw(window);
        window.display();
    }
    return 0;
}