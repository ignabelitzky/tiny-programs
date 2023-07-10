#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "population.h"
#include "target.h"

// Definition of the extern variables
int count = 0;      // Counter variable for tracking lifespan
int reached = 0;    // Counter variable for tracking how many rockets reached the target
int generation = 1;
sf::Texture rocketTexture;

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Smart Rockets");
    window.setVerticalSyncEnabled(true);

    rocketTexture.loadFromFile("./resources/images/rocket.png");

    // Creating the target
    sf::Vector2f targetPosition(width / 2.f, targetRadius + 10);
    Target target(targetPosition, targetRadius);

    // Creating the population of rockets
    Population population(population_size);

    // Setting up the text for displaying reached rocket count
    sf::Text text;
    sf::Font font;
    if(!font.loadFromFile("./resources/fonts/arial/arial.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
        return 1;
    }
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);

    bool firstTime = true;

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

        if(firstTime) {
            firstTime = false;
            std::string t = "Population size: " + std::to_string(population_size) +
                "\nImpact count: " + std::to_string(reached) + 
                "\nGeneration: " + std::to_string(generation);
            text.setString(t);
            ++generation;
        }
        // Check if lifespan is reached
        if(count == lifespan) {
            population.evaluate(target.getPosition());  // Evaluate the rockets
            population.selection(); // Perform selection and create new generation
            std::string t = "Population size: " + std::to_string(population_size) +
                "\nImpact count: " + std::to_string(reached) + 
                "\nGeneration: " + std::to_string(generation);
            text.setString(t);
            count = 0;      // Reset the lifespan counter
            reached = 0;    // Reset the reached rocket counter
            ++generation;
        }

        window.draw(text);
        
        // Showing the target
        target.update();
        target.show(window);

        window.display();
    }
    return 0;
}
