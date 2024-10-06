#include "../include/params.hpp"
#include "../include/utils.hpp"
#include "../include/walker.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Random Walker");
    window.setFramerateLimit(60);
    
    std::vector<Walker*> walkers(5);
    for (size_t i = 0; i < walkers.size(); i++)
    {
        walkers[i] = new Walker();
    }
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (size_t i = 0; i < walkers.size(); i++)
        {
            walkers[i]->step();
            walkers[i]->display(window);
        }
        window.display();
    }

    // Free memory
    for(size_t i = 0; i < walkers.size(); i++)
    {
        delete walkers[i];
    }

    return 0;
}