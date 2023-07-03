#include "ray.h"
#include "boundary.h"
#include "particle.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Ray Casting");
    window.setVerticalSyncEnabled(true);

    // Map
    Boundary leftWall(50, 50, 50, height - 50);
    Boundary rightWall(width - 50, 50, width - 50, height - 50);
    Boundary topWall(50, 50, width - 50, 50);
    Boundary bottomWall(50, height - 50, width - 50, height - 50);
    Boundary w1(150, 150, 650, 500);
    Boundary w2(650, 500, 500, 100);
    Boundary w3(1400, 350, 620, 700);
    std::vector<Boundary> walls;
    walls.push_back(leftWall);
    walls.push_back(rightWall);
    walls.push_back(topWall);
    walls.push_back(bottomWall);
    walls.push_back(w1);
    walls.push_back(w2);
    walls.push_back(w3);

    Particle particle;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        window.clear();
        for(int i = 0; i < walls.size(); ++i) {
            walls[i].show(window);
        }
        particle.update(mousePosition.x, mousePosition.y);
        particle.show(window);
        particle.look(window, walls);
        window.display();
    }
    return 0;
}
