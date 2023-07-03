#include "ray.h"
#include "boundary.h"
#include "particle.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Ray Casting");
    window.setVerticalSyncEnabled(true);

    Boundary wall(100, 200, 350, 400);
    Particle particle;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        window.clear();
        wall.show(window);
        particle.update(mousePosition.x, mousePosition.y);
        particle.show(window);
        particle.look(window, wall);
        window.display();
    }
    return 0;
}
