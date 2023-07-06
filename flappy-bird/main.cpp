#include <SFML/Graphics.hpp>
#include "params.h"
#include "helper.h"
#include "bird.h"
#include "pipe.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Flappy Bird");
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;
    sf::Time elapsedtime;
    
    // Time to generate new pipe
    float limitSecond = getRandomFloat(1.f, 2.f);
    
    // Bird start position
    sf::Vector2f birdPosition(birdStartPositionX, birdStartPositionY);

    // Pipe start position
    sf::Vector2f pipePosition(pipeStartPositionX, pipeStartPositionY);
     
    
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

        for(std::vector<Pipe>::iterator it = pipes.begin(); it != pipes.end();  ) {
            it->update();
            if(it->isOffscreen()) {
                it = pipes.erase(it);
            } else {
                if(it->hit(bird)) {
                    // Here we should discount lives
                }
                it->show(window);
                ++it;
            }
        }

        bird.show(window);

        window.display();
    }
    return 0;
}
