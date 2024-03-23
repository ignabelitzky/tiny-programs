#include <iostream>
#include <vector>
#include <deque>
#include "drop.h"
#include "splash.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Rain");
    window.setVerticalSyncEnabled(true);

    std::vector<Drop> drops;
    std::deque<Splash> splashes;
    for (size_t i = 0; i < dropCount; ++i)
    {
        Drop d;
        drops.push_back(d);
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(230, 230, 250));

        for (auto &drop : drops)
        {
            drop.fall();
            drop.show(window);
            if (drop.getPosition().y > height - 0.1f)
            {
                splashes.emplace_back(drop.getPosition());
            }
        }

        for (auto &splash : splashes)
        {
            splash.update();
            splash.show(window);
        }

        if (splashes.size() > 60)
        {
            splashes.erase(splashes.begin(), splashes.begin() + 30);
        }

        window.display();
    }
    return 0;
}
