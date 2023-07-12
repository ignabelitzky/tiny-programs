#include "GameManager.hpp"

GameManager::GameManager() : m_window(sf::VideoMode(windowWidth, windowHeight), "Sonic"), m_isRunning(true) {
    m_window.setVerticalSyncEnabled(true);
    // Additional initialization code goes here
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
    }
}

void GameManager::update() {
    // Update game logic here
}

void GameManager::render() {
    m_window.clear();
    // Render game object here
    m_window.display();
}
