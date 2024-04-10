#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/params.hpp"
#include "../include/utils.hpp"

struct Particle {
    sf::Vector2f originalPosition;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float radius;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fireworks Simulation");
    window.setFramerateLimit(60);
    std::vector<Particle> particles;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();

        // Create new fireworks
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            for(int i = 0; i < PARTICLE_MULTIPLIER; ++i)
            {
                Particle particle;
                particle.originalPosition = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                particle.position = particle.originalPosition;
                particle.velocity = sf::Vector2f(generate_random_float(-5.0f, 5.0f), generate_random_float(-5.0f, 5.0f));
                particle.color = sf::Color(generate_random_int(0, 255), generate_random_int(0, 255), generate_random_int(0, 255));
                particle.radius = generate_random_float(50.0f, 150.0f);
                particles.push_back(particle);
            }
        }

        // Update and draw particles
        for(auto& particle : particles)
        {
            particle.position += particle.velocity;
            particle.velocity.y += 0.1f;
            sf::CircleShape circle(PARTICLE_SIZE);
            circle.setFillColor(particle.color);
            circle.setPosition(particle.position);
            window.draw(circle);
            float distance = std::sqrt(std::pow(particle.position.x - particle.originalPosition.x, 2) + std::pow(particle.position.y - particle.originalPosition.y, 2));
            if(distance > particle.radius)
            {
                particles.erase(particles.begin());
            }
        }
        window.display();
    }

    return 0;
}