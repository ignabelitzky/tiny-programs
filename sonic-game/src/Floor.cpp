#include "Floor.hpp"

Floor::Floor() {
    loadTexture();

    sf::Sprite s(m_texture);
    s.setPosition(0, windowHeight - s.getGlobalBounds().height);
    m_floorSprites.push_back(s); 

    float spriteWidth = s.getGlobalBounds().width;

    for(int i = 1; i <= std::ceil(windowWidth/spriteWidth)*2; ++i) {
        sf::Sprite sprite(m_texture);
        sprite.setPosition(m_floorSprites.at(i-1).getPosition().x + m_floorSprites.at(i-1).getGlobalBounds().width,
                           windowHeight - sprite.getGlobalBounds().height);
        m_floorSprites.push_back(sprite);
    }
}

void Floor::update(float dt) {
    for(size_t i = 0; i < m_floorSprites.size(); ++i) {
        float movement = floorSpeed * dt;
        m_floorSprites.at(i).move(-movement, 0.0f);
        if(m_floorSprites.at(i).getPosition().x < 0 - m_floorSprites.at(i).getGlobalBounds().width) {
            sf::Vector2f position(windowWidth, m_floorSprites.at(i).getPosition().y);
            m_floorSprites.at(i).setPosition(position);
        }
    }
}

std::vector<sf::Sprite> Floor::getSprites() {
    return m_floorSprites;
}

void Floor::loadTexture() {
    std::string filename = "./assets/sprites/grass.png";
    if(!m_texture.loadFromFile(filename)) {
        std::cout << "Error: Grass texture not loaded!\n";
    }
}
