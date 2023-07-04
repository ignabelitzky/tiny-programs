#include "particle.h"

static float degreesToRadians(float degrees) {
    return degrees * (M_PI / 180.0);
}

Particle::Particle() {
    this->position = sf::Vector2f(width / 2, height / 2);
    for(int a = 0; a < 360; a += 5) {
        Ray ray(this->position, degreesToRadians(a));
        this->rays.push_back(ray);
    }
}

Particle::~Particle() {
}

void Particle::show(sf::RenderWindow& window) {
    sf::CircleShape circle;
    circle.setOrigin(1.0, 1.0);
    circle.setPosition(this->position);
    circle.setRadius(1.0f);
    /*
    for(size_t i = 0; i < this->rays.size(); ++i) {
        this->rays.at(i).show(window);
    }
    */
    window.draw(circle);
}

void Particle::look(sf::RenderWindow& window, std::vector<Boundary> boundaries) {
    for(size_t i = 0; i < this->rays.size(); ++i) {
        std::optional<sf::Vector2f> closest = std::nullopt;
        std::optional<sf::Vector2f> intersection = std::nullopt;
        float record = std::numeric_limits<float>::infinity();
        for(size_t j = 0; j < boundaries.size(); ++j) {
            intersection = this->rays[i].cast(boundaries[j]);
            if(intersection.has_value()) {
                float dist = std::hypot(intersection.value().x - this->position.x, intersection.value().y - this->position.y);
                if(dist < record) {
                    record = dist;
                    closest = intersection;
                }
            }
        }
        if(closest.has_value()) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = this->position;
            line[0].color = sf::Color::Yellow;
            line[1].position = closest.value();
            line[1].color = sf::Color::Yellow;
            window.draw(line);
        }
    }
}

void Particle::update(float x, float y) {
    this->position.x = x;
    this->position.y = y;
    for(size_t i = 0; i < this->rays.size(); ++i) {
        rays.at(i).setPosition(x, y);
    }
}
