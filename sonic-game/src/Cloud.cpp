#include "Cloud.hpp"

Cloud::Cloud(sf::Vector2f position) : m_velocity(0.0f, 0.0f) {
    m_shape.setPosition(position);
    m_shape.setSize(sf::Vector2f(getRandomFloat(140.0f, 200.0f), getRandomFloat(90.0f, 120.0f)));
    loadTextures();
    if(getRandomFloat(0.0f, 1.0f) < 0.5f) {
        m_texture = m_textures.at(0);
    } else {
        m_texture = m_textures.at(1);
    }
    m_cloudVelocity = getRandomFloat(floorSpeed - 5.0f, floorSpeed + 5.0f);
}

void Cloud::update(float deltaTime) {
    m_velocity.x = -m_cloudVelocity * deltaTime;
    m_shape.move(m_velocity);
}

sf::RectangleShape Cloud::getShape() {
    m_shape.setTexture(&m_texture);
    return m_shape;
}

sf::Vector2f Cloud::getPosition() {
    return m_shape.getPosition();
}

void Cloud::loadTextures() {
    for(int i = 1; i <= 2; ++i) {
        sf::Texture texture;
        std::string filename = "./assets/sprites/cloud" + std::to_string(i) + ".png";
        if(!texture.loadFromFile(filename)) {
            std::cout << "Failed to load " << filename << std::endl;
        }
        m_textures.push_back(texture);
    }
}
