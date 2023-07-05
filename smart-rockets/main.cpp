#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "population.h"

// Definition of the extern variables
int count = 0;
int reached = 0;

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Smart Rockets");
    window.setVerticalSyncEnabled(true);

    float radius = 25.0f;
    sf::CircleShape target(radius);
    target.setFillColor(sf::Color::Red);
    target.setOrigin(radius, radius);
    target.setPosition(width / 2.0f, radius + 10);

    Population population(200);

    sf::Text text;
    sf::Font font;
    if(!font.loadFromFile("./arial/arial.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
        return 1;
    }
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        population.run(window, target.getPosition());
        ++count;
        if(count == lifespan) {
            population.evaluate(target.getPosition());
            population.selection();
            std::string t = "Reached: " + std::to_string(reached);
            text.setString(t);
            count = 0;
            reached = 0;
        }
        window.draw(text);
        window.draw(target);
        window.display();
    }
    return 0;
}
