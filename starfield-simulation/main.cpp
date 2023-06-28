#include <random>
#include <SFML/Graphics.hpp>
#include "params.h"

class Star {
    public:
    sf::Vector2f position;

    Star(float a, float b) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> randomX(0, a);
        std::uniform_real_distribution<float> randomY(0, b);
        position.x = randomX(gen);
        position.y = randomY(gen);
    }

    void update(float width, float height) {
        if(position.x > width/2) {
            position.x += VELOCITY;
        } else {
            position.x -= VELOCITY;
        }
        if(position.y > height/2) {
            position.y += VELOCITY;
        } else {
            position.y -= VELOCITY;
        }
    }
};

int main() {
    constexpr int windowWidth = 800;
    constexpr int windowHeight = 400;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Starfield Simulation");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> randSize(0.5f, 1.5f);

    std::vector<Star> stars;
    for(int i = 0; i < 200; ++i) {
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
            it->update(windowWidth, windowHeight);
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
