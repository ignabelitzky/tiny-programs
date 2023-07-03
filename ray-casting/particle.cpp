#include "particle.h"

static float degreesToRadians(float degrees) {
    return degrees * (M_PI / 180.0);
}

Particle::Particle() {
    this->position = sf::Vector2f(width / 2, height / 2);
    for(int a = 0; a < 360; a += 10) {
        Ray ray(this->position, degreesToRadians(a));
        this->rays.push_back(ray);
    }
}

Particle::~Particle() {
}

void Particle::show(sf::RenderWindow& window) {
    sf::CircleShape circle;
    circle.setOrigin(0.1, 0.1);
    circle.setPosition(this->position);
    circle.setRadius(0.1f);
    for(int i = 0; i < this->rays.size(); ++i) {
        this->rays.at(i).show(window);
    }
    window.draw(circle);
}

void Particle::look(sf::RenderWindow& window, Boundary b) {
    for(int i = 0; i < this->rays.size(); ++i) {
        auto intersection = rays.at(i).cast(b);
        if(intersection.has_value()) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = this->position;
            line[1].position = intersection.value();
            window.draw(line);
        }
    }
}

void Particle::update(float x, float y) {
    this->position.x = x;
    this->position.y = y;
    for(int i = 0; i < this->rays.size(); ++i) {
        rays.at(i).setPosition(x, y);
    }
}
