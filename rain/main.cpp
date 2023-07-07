#include <iostream>
#include <vector>
#include <deque>
#include "drop.h"
#include "splash.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Rain");
    window.setVerticalSyncEnabled(true);

    std::vector<Drop> drops;
    std::deque<Splash> splashes;
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
            if(drops.at(i).getPosition().y > height - 0.1f) {
                Splash s(drops.at(i).getPosition());
                splashes.push_back(s);
            }
        }
        for(size_t i = 0; i < splashes.size(); ++i) {
            splashes.at(i).update();
            splashes.at(i).show(window);
        }

        if(splashes.size() > 60) {
            for(int i = 0; i < 30; ++i) {
                splashes.pop_front();
            }
        }

        window.display();
    }
    return 0;
}
