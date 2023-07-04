#include "drop.h"

static float map(float value, float inputMin, float inputMax, float outputMin, float outputMax) {
    float inputRange = inputMax - inputMin;
    float outputRange = outputMax - outputMin;

    // Calculate the normalized position of the value in the input range
    float normalizedPosition = (value - inputMin) / inputRange;

    // Map the normalized position to the output range
    float mappedValue = (normalizedPosition * outputRange) + outputMin;

    return mappedValue;
}

Drop::Drop() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDis(0.0f, width);
    std::uniform_real_distribution<float> yDis(-200.0f, -50.0f);
    std::uniform_real_distribution<float> zDis(0.0f, 20.0f);
    std::uniform_real_distribution<float> velDis(1.0f, 4.0f);
    std::uniform_real_distribution<float> lenDis(6.0f, 10.0f);
    this->position = sf::Vector2f(xDis(gen), yDis(gen));
    this->z = zDis(gen);
    this->length = map(this->z, 0.0f, 20.0f, 10.0f, 20.0f);
    this->ySpeed = map(this->z, 0.0f, 20.0f, 2.0f, 7.0f);
}

Drop::~Drop() {
}

void Drop::restartDrop() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDis(0.0f, width);
    std::uniform_real_distribution<float> yDis(-height * 0.8f, -50.0f);
    std::uniform_real_distribution<float> zDis(0.0f, 20.0f);
    std::uniform_real_distribution<float> velDis(1.0f, 4.0f);
    std::uniform_real_distribution<float> lenDis(6.0f, 10.0f);
    this->position = sf::Vector2f(xDis(gen), yDis(gen));
    this->z = zDis(gen);
    this->length = map(this->z, 0.0f, 20.0f, 10.0f, 20.0f);
    this->ySpeed = map(this->z, 0.0f, 20.0f, 4.0f, 10.0f);
}

void Drop::fall() {
    this->position.y += this->ySpeed;
    this->position.y += 0.2f;
    if(this->position.y > height)
        this->restartDrop();
}

void Drop::show(sf::RenderWindow& window) {
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = this->position;
    line[0].color = sf::Color(138, 43, 226);
    line[1].position = this->position + sf::Vector2f(0.0f, this->length);
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
