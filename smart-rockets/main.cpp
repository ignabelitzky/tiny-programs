#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "population.h"

// Definition of the extern variables
int count = 0;      // Counter variable for tracking lifespan
int reached = 0;    // Counter variable for tracking how many rockets reached the target

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Smart Rockets");
    window.setVerticalSyncEnabled(true);

    float radius = 25.0f;

    // Creating the target circle shape
    sf::CircleShape target(radius);
    target.setFillColor(sf::Color::Red);
    target.setOrigin(radius, radius);
    target.setPosition(width / 2.0f, radius + 10);

    // Creating the population of rockets
    Population population(200);

    // Setting up the text for displaying reached rocket count
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

        // Run the population, update and render rockets
        population.run(window, target.getPosition());

        ++count; // Increment the lifespan counter

        // Check if lifespan is reached
        if(count == lifespan) {
            population.evaluate(target.getPosition());  // Evaluate the rockets
            population.selection(); // Perform selection and create new generation
            std::string t = "Reached: " + std::to_string(reached);
            text.setString(t);
            count = 0;      // Reset the lifespan counter
            reached = 0;    // Reset the reached rocket counter
        }

        window.draw(text);
        window.draw(target);

        window.display();
    }
    return 0;
}
