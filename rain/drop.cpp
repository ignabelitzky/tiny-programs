#include "drop.h"

Drop::Drop() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDis(0.0f, width);
    std::uniform_real_distribution<float> velDis(1.0f, 1.5f);
    this->position = sf::Vector2f(xDis(gen), 0.0f);
    this->ySpeed = velDis(gen);
}

Drop::~Drop() {
}

void Drop::fall() {
    this->position.y += this->ySpeed;
}

void Drop::show(sf::RenderWindow& window) {
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = this->position;
    line[0].color = sf::Color(138, 43, 226);
    line[1].position = this->position + sf::Vector2f(0.0f, 10.0);
    line[1].color = sf::Color(138, 43, 226);
    window.draw(line);
}

sf::Vector2f Drop::getPosition() {
    return this->position;
}

void Drop::setPosition(float x, float y) {
    this->position.x = x;
    this->position.y = y;
}
