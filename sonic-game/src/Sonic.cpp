#include "Sonic.hpp"

Sonic::Sonic(sf::Vector2f position, float groundLevel, float skyLevel) :
        m_velocity(0.0f, 0.0f), m_isJumping(false), m_jumpSpeed(100.0f),
        m_groundLevel(groundLevel), m_skyLevel(skyLevel), m_bounceFactor(0.5f),
        m_runIndex(0) {
    float radius = 50.0f;
    m_shape.setPosition(position);
    m_shape.setRadius(radius);
    m_shape.setOrigin(radius, radius);

    // Load of jump sprites
    for(int i = 1; i <= 8; ++i) {
        sf::Texture texture;
        std::string filename = "./assets/sprites/jump" + std::to_string(i) + ".png";
        if(!texture.loadFromFile(filename)) {
            std::cout << "Failed to load " << filename << std::endl;
        }
        m_jumpTextures.push_back(texture);
    }

    // Load of run sprites
    for(int  i = 1; i <= 16; ++i) {
        sf::Texture texture;
        std::string filename = "./assets/sprites/run" + std::to_string(i) + ".png";
        if(!texture.loadFromFile(filename)) {
            std::cout << "Failed to load " << filename << std::endl;
        }
        m_runTextures.push_back(texture);
    }
    m_shape.setTexture(&m_runTextures.at(0));
    //float scaleX = m_shape.getRadius() * 2.0f / m_runTextures.at(0).getSize().x;
    //float scaleY = m_shape.getRadius() * 2.0f / m_runTextures.at(0).getSize().y;
    float scaleX = 1.3f;
    float scaleY = 1.3f;
    sf::IntRect textureRect(0, 0, m_runTextures.at(0).getSize().x * scaleX, m_runTextures.at(0).getSize().y * scaleY);
    m_shape.setTextureRect(textureRect);
    m_frameDuration = sf::seconds(0.08f);
    m_elapsed = m_clock.getElapsedTime();
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

    m_elapsed = m_clock.getElapsedTime();
    if(m_elapsed >= m_frameDuration) {
        m_clock.restart();
        if(m_runIndex != m_runTextures.size()-1) {
            ++m_runIndex;
        } else {
            m_runIndex = 0;
        }
        m_shape.setTexture(&m_runTextures.at(m_runIndex));
    }
}

void Sonic::jump() {
    if(!m_isJumping)
        m_isJumping = true;
}

sf::CircleShape Sonic::getShape() {
    return m_shape;
}
