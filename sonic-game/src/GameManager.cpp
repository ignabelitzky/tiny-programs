#include "GameManager.hpp"

GameManager::GameManager() : m_window(sf::VideoMode(windowWidth, windowHeight), "Sonic"), m_isRunning(true),
    m_player(sf::Vector2f(sonicXPos, sonicYPos), groundLevel, skyLevel) {
    m_window.setVerticalSyncEnabled(true);
    m_frameDuration = sf::seconds(0.08f);
    m_elapsed = m_clock.getElapsedTime();
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
    m_player.update(0.5);

    m_elapsed = m_clock.getElapsedTime();
    if(m_elapsed >= m_frameDuration) {
        m_clock.restart();
        m_player.applyNextRunSprite();
    }
}

void GameManager::render() {
    m_window.clear();
    m_window.draw(m_player.getShape());
    m_window.draw(m_player.getSprite());
    m_window.display();
}
