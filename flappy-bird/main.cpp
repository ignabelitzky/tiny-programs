#include <iostream>
#include <SFML/Graphics.hpp>
#include "params.h"
#include "bird.h"
#include "pipe.h"

static float getRandomFloat(float min, float max) {
    // Obtain a random seed using the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create a random number generator engine
    std::default_random_engine generator(std::rand());

    // Create a distribution to define the range
    std::uniform_real_distribution<float> distribution(min, max);

    // Generate and return a random float within the range
    return distribution(generator);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Flappy Bird");
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;
    sf::Time elapsedtime;
    
    float limitSecond = getRandomFloat(1.f, 3.f);
    
    int birdRadius = 30;
    sf::Vector2f birdPosition(120, height/2);
    sf::Vector2f pipePosition(width, 0);
     
    
    Bird bird(birdRadius, birdPosition);
    std::vector<Pipe> pipes;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // Get the elapsed time
        elapsedtime = clock.getElapsedTime();


        if(elapsedtime.asSeconds() >= limitSecond) {
            Pipe pipe(pipePosition);
            pipes.push_back(pipe);
           
            // Reset the clock
            clock.restart();
            limitSecond = getRandomFloat(0.5f, 1.5f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            bird.up();
        }

        window.clear();

        bird.update();

        std::cout << "Vector size: " << pipes.size() << std::endl;

        for(std::vector<Pipe>::iterator it = pipes.begin(); it != pipes.end();  ) {
            it->update();
            if(it->isOffscreen()) {
                it = pipes.erase(it);
            } else {
                it->show(window);
                ++it;
            }
        }

        bird.show(window);

        window.display();
    }
    return 0;
}
