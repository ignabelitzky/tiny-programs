#include <SFML/Graphics.hpp>
#include "params.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sonic");
    window.setVerticalSyncEnabled(true);
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.display();
    }
    return 0;
}
