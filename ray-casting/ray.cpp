#include "ray.h"

static sf::Vector2f createVectorFromAngle(float angleRadians) {
    float x = std::cos(angleRadians);
    float y = std::sin(angleRadians);
    return sf::Vector2f(x, y);
}

Ray::Ray(sf::Vector2f pos, float angle) {
    this->position = pos;
    this->direction = createVectorFromAngle(angle);
    normalizeDirection();
}

Ray::~Ray() {
}

void Ray::show(sf::RenderWindow& window) {
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = this->position;
    line[1].position = this->position + this->direction;
    window.draw(line);
}

std::optional<sf::Vector2f> Ray::cast(Boundary b) {
    sf::Vector2f fst = b.getFstPoint();
    sf::Vector2f snd = b.getSndPoint();

    float x1 = fst.x, y1 = fst.y;
    float x2 = snd.x, y2 = snd.y;

    float x3 = this->position.x, y3 = this->position.y;
    float x4 = this->position.x + this->direction.x;
    float y4 = this->position.y + this->direction.y;

    float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if(den == 0) {
        return std::nullopt;
    } else {
        float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
        float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
        if(t > 0 && t < 1 && u > 0) {
            sf::Vector2f result;
            result.x = x1 + t * (x2 - x1);
            result.y = y1 + t * (y2 - y1);
            return result;
        } else {
            return std::nullopt;
        }
    }
}

void Ray::setPosition(float posX, float posY) {
    this->position = sf::Vector2f(posX, posY);
}

void Ray::normalizeDirection() {
    float length = std::sqrt(this->direction.x * this->direction.x + this->direction.y * this->direction.y);
    if(length != 0.0f) {
        this->direction.x /= length;
        this->direction.y /= length;
    }
}

void Ray::setDirection(float dirX, float dirY) {
    this->direction = sf::Vector2f(dirX, dirY);
    normalizeDirection();
}

sf::Vector2f Ray::getPosition() {
    return this->position;
}

sf::Vector2f Ray::getDirection() {
    return this->direction;
}
