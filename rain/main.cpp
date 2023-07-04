#include <iostream>
#include <vector>
#include "drop.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Rain");
    window.setVerticalSyncEnabled(true);

    std::vector<Drop> drops;
    for(size_t i = 0; i < dropCount; ++i) {
        Drop d;
        drops.push_back(d);
    }
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(230, 230, 250));
        for(size_t i = 0; i < drops.size(); ++i) {
            drops.at(i).fall();
            drops.at(i).show(window);
        }
        window.display();
    }
    return 0;
}
