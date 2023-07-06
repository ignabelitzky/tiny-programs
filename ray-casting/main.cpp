#include <random>
#include "ray.h"
#include "boundary.h"
#include "particle.h"

void mapGenerator(std::vector<Boundary>&, int);

int main() {
    // Creating the window for the ray casting visualization
    sf::RenderWindow window(sf::VideoMode(width, height), "Ray Casting");
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    // Creating a vector to store the boundaries of the map
    std::vector<Boundary> walls;

    mapGenerator(walls, numLines);

    // Creating a particle for ray casting
    Particle particle;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        // Getting the mouse position for particle movement
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Clearing the window
        window.clear();

        // Rendering and displaying the boundaries
        for(size_t i = 0; i < walls.size(); ++i) {
            walls[i].show(window);
        }

        // Updating and rendering the particle
        particle.update(mousePosition.x, mousePosition.y);
        particle.show(window);

        // Performing ray casting and rendering the rays
        particle.look(window, walls);

        // Displaying the updated window
        window.display();
    }
    return 0;
}

// Function to generate the map with random boundaries
void mapGenerator(std::vector<Boundary>& boundaries, int lines = 3) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> xDist(75.0f, width - 75.0f);
    std::uniform_real_distribution<float> yDist(75.0f, height - 75.0f);

    Boundary leftWall(50, 50, 50, height - 50);
    Boundary rightWall(width - 50, 50, width - 50, height - 50);
    Boundary topWall(50, 50, width - 50, 50);
    Boundary bottomWall(50, height - 50, width - 50, height - 50);

    boundaries.push_back(leftWall);
    boundaries.push_back(rightWall);
    boundaries.push_back(topWall);
    boundaries.push_back(bottomWall);

    for(int i = 0; i < lines; ++i) {
        Boundary b(xDist(gen), yDist(gen), xDist(gen), yDist(gen));
        boundaries.push_back(b);
    }
}
