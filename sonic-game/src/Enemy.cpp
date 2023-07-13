#include "Enemy.hpp"

Enemy::Enemy(sf::Vector2f position) :
        m_velocity(0.0f, 0.0f), m_textureIndex(0), m_passed(false) {
    m_shape.setPosition(position);
    m_shape.setRadius(enemyRadius);
    m_shape.setOrigin(enemyRadius, enemyRadius);

    loadTextures();

    m_shape.setTexture(&m_textures.at(m_textureIndex));

    m_frameDuration = sf::seconds(frameDuration);
    m_elapsed = m_clock.getElapsedTime();
}

void Enemy::update(float deltaTime) {
    m_velocity.x = -enemyVelocity * deltaTime;
    m_shape.move(m_velocity);
    m_elapsed = m_clock.getElapsedTime();
    if(m_elapsed >= m_frameDuration) {
        m_clock.restart();
        m_textureIndex = (m_textureIndex != m_textures.size()-1) ? m_textureIndex + 1 : 0;
        m_shape.setTexture(&m_textures.at(m_textureIndex));
    }
}

sf::CircleShape Enemy::getShape() {
    return m_shape;
}

sf::Vector2f Enemy::getPosition() {
    return m_shape.getPosition();
}

float Enemy::getRadius() {
    return m_shape.getRadius();
}

bool Enemy::isPassed() {
    return m_passed;
}

void Enemy::setPassed(bool value) {
    m_passed = value;
}

void Enemy::loadTextures() {
    for(int i = 1; i <= enemySpritesCount; ++i) {
        sf::Texture texture;
        std::string filename = "./assets/sprites/enemy" + std::to_string(i) + ".png";
        if(!texture.loadFromFile(filename)) {
            std::cout << "Failed to load " << filename << std::endl;
        }
        m_textures.push_back(texture);
    }
}
