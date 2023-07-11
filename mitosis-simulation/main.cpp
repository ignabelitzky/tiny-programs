#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "params.h"
#include "cell.h"
#include "helper.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Mitosis Simulation");
    window.setVerticalSyncEnabled(true);
    sf::View view(window.getDefaultView());
    sf::Vector2i lastMousePos;
    std::vector<Cell> cells;
    for(size_t i = 0; i < cellsSize; ++i) {
        sf::Vector2f rndPos(genRandomFloat(0, windowWidth), genRandomFloat(0, windowHeight));
        Cell cell(rndPos, cellRadius);
        cells.push_back(cell);
    }
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();

            // Zoom in and out
            if(event.type == sf::Event::MouseWheelScrolled) {
                    if(event.mouseWheelScroll.delta > 0)
                        view.zoom(0.8f);
                    if(event.mouseWheelScroll.delta < 0)
                        view.zoom(1.2f);
            }

            // Pan movement
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Right)
                    lastMousePos = sf::Mouse::getPosition(window);
                else if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    for(int i = (int)cells.size()-1; i >= 0; --i) {
                        if(cells.at(i).mousePressed(mousePosition)) {
                            cells.push_back(cells.at(i).mitosis());
                            cells.push_back(cells.at(i).mitosis());
                            cells.erase(cells.begin() + i);
                            std::cout << "New cells created through mitosis.\n";
                        }
                    }
                }
            } 

            if(event.type == sf::Event::MouseMoved)
                if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                    sf::Vector2i delta = currentMousePos - lastMousePos;
                    view.move(-delta.x, -delta.y);
                    lastMousePos = currentMousePos;
                }
        }
        window.setView(view);
        window.clear();
        for(size_t i = 0; i < cells.size(); ++i) {
            cells.at(i).move();
            cells.at(i).show(window);
        }
        window.display();
    }

    return 0;
}
