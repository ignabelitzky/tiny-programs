#include <random>
#include "ray.h"
#include "boundary.h"
#include "particle.h"

void mapGenerator(std::vector<Boundary>&, int);

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Ray Casting");
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    std::vector<Boundary> walls;
    mapGenerator(walls, numLines);

    Particle particle;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        window.clear();
        for(size_t i = 0; i < walls.size(); ++i) {
            walls[i].show(window);
        }
        particle.update(mousePosition.x, mousePosition.y);
        particle.show(window);
        particle.look(window, walls);
        window.display();
    }
    return 0;
}

void mapGenerator(std::vector<Boundary>& a, int lines = 3) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> xDist(75.0f, width - 75.0f);
    std::uniform_real_distribution<float> yDist(75.0f, height - 75.0f);

    Boundary leftWall(50, 50, 50, height - 50);
    Boundary rightWall(width - 50, 50, width - 50, height - 50);
    Boundary topWall(50, 50, width - 50, 50);
    Boundary bottomWall(50, height - 50, width - 50, height - 50);

    a.push_back(leftWall);
    a.push_back(rightWall);
    a.push_back(topWall);
    a.push_back(bottomWall);

    for(int i = 0; i < lines; ++i) {
        Boundary b(xDist(gen), yDist(gen), xDist(gen), yDist(gen));
        a.push_back(b);
    }
}
