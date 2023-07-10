#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "population.h"
#include "target.h"

// Definition of the extern variables
int count = 0;      // Counter variable for tracking lifespan
int reached = 0;    // Counter variable for tracking how many rockets reached the target
int lastReached = 0;
int generation = 1;
sf::Texture rocketTexture;

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Smart Rockets");
    sf::View view(window.getDefaultView());
    sf::Vector2i lastMousePos;
    window.setVerticalSyncEnabled(true);

    rocketTexture.loadFromFile("./resources/images/rocket.png");

    // Creating the target
    sf::Vector2f targetPosition(width - targetRadius - 10.f, height / 2.f);
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
    //text.setPosition(10, 10);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
            // Zoom in
            if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.delta > 0)
                view.zoom(0.8f);

            // Zoom out
            if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.delta < 0)
                view.zoom(1.2f);

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    lastMousePos = sf::Mouse::getPosition(window);
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                    sf::Vector2i delta = currentMousePos - lastMousePos;
                    view.move(-delta.x, -delta.y);

                    lastMousePos = currentMousePos;
                }
            }
        }
        window.setView(view);
        window.clear();

        // Run the population, update and render rockets
        population.run(window, target.getPosition());

        ++count; // Increment the lifespan counter

        // Check if lifespan is reached
        if(count == lifespan) {
            population.evaluate(target.getPosition());  // Evaluate the rockets
            population.selection(); // Perform selection and create new generation
            count = 0;
            lastReached = reached;
            reached = 0;
            ++generation;
        }
        std::string t = "Population size: " + std::to_string(population_size) +
            "\nLifespan: " + std::to_string(lifespan) +
            "\nImpact count: " + std::to_string(lastReached) + 
            "\nGeneration: " + std::to_string(generation);
        text.setString(t);
        sf::Vector2f textPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y/ 2);
        text.setPosition(textPosition);

        float zoomFactor = view.getSize().x / window.getSize().x; // Assuming a fixed aspect ratio
        text.setScale(zoomFactor, zoomFactor);

        window.draw(text);
        
        // Showing the target
        target.update();
        target.show(window);

        window.display();
    }
    return 0;
}
