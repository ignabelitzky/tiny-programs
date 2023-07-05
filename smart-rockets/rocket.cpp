#include "rocket.h"

static float map(float value, float inputMin, float inputMax, float outputMin, float outputMax) {
    float inputRange = inputMax - inputMin;
    float outputRange = outputMax - outputMin;

    // Calculate the normalized position of the value in the input range
    float normalizedPosition = (value - inputMin) / inputRange;

    // Map the normalized position to the output range
    float mappedValue = (normalizedPosition * outputRange) + outputMin;

    return mappedValue;
}


static float calculateAngleDirection(const sf::Vector2f& vector) {
    float x = vector.x;
    float y = vector.y;

    // Normalize the vector
    float length = std::sqrt(x*x + y*y);
    x /= length;
    y /= length;

    return std::atan2(y, x) * 180.0f / M_PI;
}

Rocket::Rocket() {
    this->position = sf::Vector2f(width/2.0f, height - 10.0f);
    this->velocity = sf::Vector2f(0.0f, 0.0f);
    this->acceleration = sf::Vector2f(0.0f, 0.0f);
    this->rotationAngle = 0.0f;
    this->fitness = 0.0f;
    this->completed = false;
    this->crashed = false;
}

Rocket::Rocket(DNA d) {
    this->position = sf::Vector2f(width/2.0f, height - 10.0f);
    this->velocity = sf::Vector2f(0.0f, 0.0f);
    this->acceleration = sf::Vector2f(0.0f, 0.0f);
    this->rotationAngle = 0.0f;
    this->fitness = 0.0f;
    this->dna = d;
    this->completed = false;
    this->crashed = false;
}

Rocket::~Rocket() {
}

void Rocket::applyForce(sf::Vector2f force) {
    this->acceleration += force;
}

void Rocket::calcFitness(sf::Vector2f targetPos) {
    float deltaX = targetPos.x - this->position.x;
    float deltaY = targetPos.y - this->position.y;
    float d = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    this->fitness = map(d, 0.0f, width, width, 0.0f);
    if(this->completed) {
        this->fitness *= 10.0f;
    }
    if(this->crashed && !this->completed) {
        this->fitness /= 10;
    }
}

void Rocket::update(sf::Vector2f targetPos) {
    float deltaX = targetPos.x - this->position.x;
    float deltaY = targetPos.y - this->position.y;
    float d = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    if(d < 10) {
        if(!this->completed) {
            ++reached;
        }
        this->completed = true;
        this->position = targetPos;
    }
    if(this->position.x > width || this->position.x < 0) {
        this->crashed = true;
    }
    if(this->position.y < 0 || this->position.y > height) {
        this->crashed = true;
    }
    this->applyForce(this->dna.getGene(count));
    if(!this->completed && !this->crashed) {
        this->velocity += this->acceleration;
        this->position += this->velocity;
        this->acceleration = sf::Vector2f(0.0f, 0.0f);
        this->rotationAngle = calculateAngleDirection(this->velocity);
    }
}

void Rocket::show(sf::RenderWindow& window) {
    sf::RectangleShape rocket(sf::Vector2f(25, 5));
    rocket.setFillColor(sf::Color::White);
    rocket.setOrigin(rocket.getSize() / 2.0f);
    rocket.setRotation(this->rotationAngle);
    rocket.setPosition(this->position.x, this->position.y);
    window.draw(rocket);
}

float Rocket::getFitness() {
    return this->fitness;
}

void Rocket::setFitness(float f) {
    this->fitness = f;
}

DNA Rocket::getDNA() {
    return this->dna;
}
