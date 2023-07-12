#include "Sonic.hpp"

Sonic::Sonic(sf::Vector2f position, float groundLevel, float skyLevel) : m_shape(sf::Vector2f(50.0f, 100.0f)),
        m_velocity(0.0f, 0.0f), m_isJumping(false), m_jumpSpeed(100.0f),
        m_groundLevel(groundLevel), m_skyLevel(skyLevel), m_bounceFactor(0.5f) {
    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color::Red);
}

void Sonic::update(float deltaTime) {
    if(m_isJumping) {
        m_velocity.y -= m_jumpSpeed;
        m_isJumping = false;
    }
    // Apply gravity to the player's velocity
    m_velocity.y += 9.8f * deltaTime;

    // Update player position based on velocity
    m_shape.move(m_velocity * deltaTime);

    // Check if player has reached or passed the ground level
    if(m_shape.getPosition().y >= m_groundLevel) {
        // Reset player position to ground level
        m_shape.setPosition(m_shape.getPosition().x, m_groundLevel);

        // Reverse vertical velocity with bounce factor
        m_velocity.y = -m_velocity.y * m_bounceFactor;
    }

    // Check if player has reached or passed the sky level
    if(m_shape.getPosition().y <= m_skyLevel) {
        // Reset player position to sky level
        m_shape.setPosition(m_shape.getPosition().x, m_skyLevel);

        // Reverse vertical velocity with bounce factor
        m_velocity.y = -m_velocity.y * m_bounceFactor;
    }
}

void Sonic::jump() {
    if(!m_isJumping)
        m_isJumping = true;
}

sf::RectangleShape Sonic::getShape() {
    return m_shape;
}
