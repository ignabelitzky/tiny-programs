#include "Sonic.hpp"

Sonic::Sonic(sf::Vector2f position, float groundLevel, float skyLevel) :
        m_velocity(0.0f, 0.0f), m_isJumping(false), m_jumpSpeed(jumpSpeed),
        m_groundLevel(groundLevel), m_skyLevel(skyLevel), m_bounceFactor(bounceFactor),
        m_runIndex(0) {
    m_shape.setPosition(position);
    m_shape.setRadius(sonicRadius);
    m_shape.setOrigin(sonicRadius, sonicRadius);

    // Loading of textures
    loadTextures();

    m_shape.setTexture(&m_runTextures.at(m_runIndex));

    m_frameDuration = sf::seconds(frameDuration);
    m_elapsed = m_clock.getElapsedTime();
}

void Sonic::update(float deltaTime) {
    if(m_isJumping) {
        m_velocity.y -= m_jumpSpeed;
        m_isJumping = false;
    }
    // Apply gravity to the player's velocity
    m_velocity.y += sonicGravity * deltaTime;

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
        m_runIndex = (m_runIndex != m_runTextures.size()-1) ? m_runIndex + 1 : 0;
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

sf::Vector2f Sonic::getPosition() {
    return m_shape.getPosition();
}

bool Sonic::collidesWith(Enemy enemy) {
    sf::Vector2f pos1 = m_shape.getPosition();
    sf::Vector2f pos2 = enemy.getPosition();

    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    float radiusSum = m_shape.getRadius() + enemy.getRadius();

    return distance < radiusSum;
}

void Sonic::loadTextures() {
    // Load of jump textures
    for(int i = 1; i <= jumpSpritesCount; ++i) {
        sf::Texture texture;
        std::string filename = "./assets/sprites/jump" + std::to_string(i) + ".png";
        if(!texture.loadFromFile(filename)) {
            std::cout << "Failed to load " << filename << std::endl;
        }
        m_jumpTextures.push_back(texture);
    }

    // Load of run textures
    for(int  i = 1; i <= runSpritesCount; ++i) {
        sf::Texture texture;
        std::string filename = "./assets/sprites/run" + std::to_string(i) + ".png";
        if(!texture.loadFromFile(filename)) {
            std::cout << "Failed to load " << filename << std::endl;
        }
        m_runTextures.push_back(texture);
    }
}

