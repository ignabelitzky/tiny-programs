#include "../include/particle.hpp"
#include "../include/utils.hpp"
#include "../include/params.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);

    std::vector<Particle *> particles;
    for (int i = 0; i < 5; ++i)
    {
        Particle *p = new Particle();
        p->setPosition(utils::random(10.0f, params::WIDTH), utils::random(10.0f, params::HEIGHT));
        p->setVelocity(utils::random(-2, 2), utils::random(-2, 2));
        p->setAcceleration(0.0f, 0.0f);
        particles.push_back(p);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (auto p : particles)
        {
            for (auto other : particles)
            {
                if (p != other)
                {
                    p->collide(other);
                }
            }
            p->update();
            p->edges();
            p->draw(window);
        }
        window.display();
    }

    return 0;
}