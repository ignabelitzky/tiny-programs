#include <iostream>
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
    m_position = sf::Vector2f(20.f, height/2.f);
    m_rocket.setPosition(m_position);
    m_velocity = sf::Vector2f(0.0f, 0.0f);
    m_acceleration = sf::Vector2f(0.0f, 0.0f);
    m_rotationAngle = 0.0f;
    m_fitness = 0.0f;
    m_completed = false;
    m_crashed = false;
}

Rocket::Rocket(DNA d) {
    m_position = sf::Vector2f(20.f, height/2.f);
    m_rocket.setPosition(m_position);
    m_velocity = sf::Vector2f(0.0f, 0.0f);
    m_acceleration = sf::Vector2f(0.0f, 0.0f);
    m_rotationAngle = 0.0f;
    m_fitness = 0.0f;
    m_dna = d;
    m_completed = false;
    m_crashed = false;
}

Rocket::~Rocket() {
}

void Rocket::applyForce(sf::Vector2f force) {
    m_acceleration += force;
}

void Rocket::calcFitness(sf::Vector2f targetPos) {
    float deltaX = targetPos.x - m_position.x;
    float deltaY = targetPos.y - m_position.y;
    float d = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    m_fitness = map(d, 0.0f, width, width, 0.0f);
    if(m_completed) {
        m_fitness *= 10;
    }
    if(m_crashed && !m_completed) {
        m_fitness /= 10;
    }
}

void Rocket::update(sf::Vector2f targetPos) {
    float deltaX = targetPos.x - m_position.x;
    float deltaY = targetPos.y - m_position.y;
    float d = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    if(d < targetRadius) {
        if(!m_completed) {
            ++reached;
        }
        m_completed = true;
        m_position = targetPos;
    }
    /* Check the walls
    if(m_position.x > width || m_position.x < 0) {
        m_crashed = true;
    }
    if(m_position.y < 0 || m_position.y > height) {
        m_crashed = true;
    }
    */
    this->applyForce(m_dna.getGene(count));
    if(!m_completed && !m_crashed) {
        m_velocity += m_acceleration;
        m_position += m_velocity;
        m_acceleration = sf::Vector2f(0.0f, 0.0f);
        m_rotationAngle = calculateAngleDirection(m_velocity);
    }
}

void Rocket::show(sf::RenderWindow& window) {
    m_rocket.setSize(sf::Vector2f(75.0f, 30.0f));
    m_rocket.setTexture(&rocketTexture);
    m_rocket.setOrigin(m_rocket.getSize() / 2.0f);
    m_rocket.setRotation(m_rotationAngle);
    m_rocket.setPosition(m_position.x, m_position.y);
    window.draw(m_rocket);
}

float Rocket::getFitness() {
    return m_fitness;
}

void Rocket::setFitness(float f) {
    m_fitness = f;
}

DNA Rocket::getDNA() {
    return m_dna;
}
