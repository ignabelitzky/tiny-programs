#include <random>
#include <SFML/Graphics.hpp>
#include "params.h"

class Star {
    public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool mustDelete;

    Star(float a, float b) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> velDist(50.0f, 100.0f);
        std::uniform_real_distribution<float> angleDist(0.0f, 2 * 3.141592f);

        position = sf::Vector2f(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
        velocity = sf::Vector2f(velDist(gen) * std::cos(angleDist(gen)), velDist(gen) * std::sin(angleDist(gen)));
        mustDelete = false;
    }

    void update() {
        position += velocity * 0.01f;
    }
};

int main() {
    constexpr int windowWidth = WINDOW_WIDTH;
    constexpr int windowHeight = WINDOW_HEIGHT;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Starfield Simulation");
    window.setFramerateLimit(60);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> randSize(0.5f, 1.0f);

    std::vector<Star> stars;
    for(int i = 0; i < NUM_STARS; ++i) {
        Star star(windowWidth, windowHeight);
        stars.push_back(star);
    }

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        // Update and draw stars
        for(auto it = stars.begin(); it != stars.end();) {
            sf::CircleShape shape(randSize(gen));
            it->update();
            shape.setPosition(it->position);
            window.draw(shape);
            if(it->position.x < 0 || it->position.x > windowWidth || it->position.y < 0 || it->position.y > windowHeight) {
                it = stars.erase(it);
                Star star(windowWidth, windowHeight);
                stars.push_back(star);
            } else {
                ++it;
            }
        }
        window.display();
    }
    return 0;
}
