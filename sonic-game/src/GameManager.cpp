#include "GameManager.hpp"

GameManager::GameManager() : m_window(sf::VideoMode(windowWidth, windowHeight), "Sonic"), m_isRunning(true),
    m_player(sf::Vector2f(sonicXPos, sonicYPos), groundLevel, skyLevel) {
    m_window.setVerticalSyncEnabled(true);
    m_enemies.push_back(Enemy(sf::Vector2f(windowWidth, windowHeight-50)));
}

void GameManager::run() {
    while(m_isRunning) {
        processEvents();
        update();
        render();
    }
    m_window.close();
}

void GameManager::processEvents() {
    sf::Event event;
    while(m_window.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            m_isRunning = false;
        if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::Up)
                m_player.jump();
        }
    }
}

void GameManager::update() {
    // Update game logic here
    m_player.update(0.5f);
    m_floor.update(0.5f);
    for(size_t i = 0; i < m_enemies.size(); ++i) {
        m_enemies.at(i).update(0.5f);
    }
}

void GameManager::render() {
    m_window.clear();
    std::vector<sf::Sprite> floor = m_floor.getSprites();
    for(size_t i = 0; i < floor.size(); ++i) {
        m_window.draw(floor.at(i));
    }
    for(size_t i = 0; i < m_enemies.size(); ++i) {
        m_window.draw(m_enemies.at(i).getShape());
    }
    m_window.draw(m_player.getShape());
    m_window.display();
}
