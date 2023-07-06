#include <SFML/Graphics.hpp>
#include "params.h"
#include "bird.h"
#include "pipe.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Flappy Bird");
    window.setVerticalSyncEnabled(true);
    
    int birdRadius = 30;
    sf::Vector2f birdPosition(120, height/2);
    sf::Vector2f pipePosition(width, 45);
     
    
    Bird bird(birdRadius, birdPosition);
    Pipe pipe(pipePosition);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            bird.up();
        }

        window.clear();

        bird.update();
        pipe.update();

        bird.show(window);
        pipe.show(window);

        window.display();
    }
    return 0;
}
