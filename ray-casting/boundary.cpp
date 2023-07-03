#include "boundary.h"

Boundary::Boundary(float x1, float y1, float x2, float y2) {
    this->fstPoint = sf::Vector2f(x1, y1);
    this->sndPoint = sf::Vector2f(x2, y2);
}

Boundary::~Boundary() {
}

void Boundary::show(sf::RenderWindow& window) {
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = this->fstPoint;
    line[1].position = this->sndPoint;
    window.draw(line);
}

sf::Vector2f Boundary::getFstPoint() {
    return this->fstPoint;
}

sf::Vector2f Boundary::getSndPoint() {
    return this->sndPoint;
}
