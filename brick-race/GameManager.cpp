#include "GameManager.hpp"

GameManager::GameManager() :
    m_window(sf::VideoMode(WIDTH, HEIGHT), "Brick Race"), m_isRunning(true),
    m_gameState(GameState::MENU), m_score(0), m_selectedOption(0)
{
    m_window.setVerticalSyncEnabled(true);
    /*
    loadBackgroundMusic();
    loadFonts();
    loadTexts();
    m_maxScore = retrieveMaxScore();
    */
}

GameManager::~GameManager() {
    m_backgroundMusic.stop();
}

void GameManager::run() {
    m_backgroundMusic.play();
    while(m_isRunning) {
        processEvents();
        switch(m_gameState) {
            case GameState::MENU:
                updateMenu();
                break;
            case GameState::PLAYING:
                updatePlaying();
                break;
            case GameState::GAME_OVER:
                updateGameOver();
                break;
            default:
                break;
        }
        render();
    }
    m_window.close();
}

void GameManager::processEvents() {
    sf::Event event;
    while(m_window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            m_isRunning = false;
        } else if(event.type == sf::Event::KeyPressed) {
            if(m_gameState == GameState::MENU) {
                handleMenuInput(event.key.code);
            } else if(m_gameState == GameState::PLAYING) {
                handlePlayingInput(event.key.code);
            } else if(m_gameState == GameState::GAME_OVER) {
                handleGameOverInput(event.key.code);
            }
        }
    }
}

void GameManager::handleMenuInput(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::Up) {
        m_selectedOption = (m_selectedOption - 1 + 2) % 2;
    } else if(key == sf::Keyboard::Down) {
        m_selectedOption = (m_selectedOption + 1) % 2;
    } else if(key == sf::Keyboard::Enter) {
        if(m_selectedOption == 0) {
            m_gameState = GameState::PLAYING;
        } else if(m_selectedOption == 1) {
            m_isRunning = false;
        }
    }
}

void GameManager::handlePlayingInput(sf::Keyboard::Key key) {
}

void GameManager::handleGameOverInput(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::Up) {
        m_selectedOption = (m_selectedOption - 1 + 2) % 2;
    } else if(key == sf::Keyboard::Down) {
        m_selectedOption = (m_selectedOption + 1) % 2;
    } else if(key == sf::Keyboard::Enter) {
        if(m_selectedOption == 0) {
            resetGame();
        } else if(m_selectedOption == 1){
            m_isRunning = false;
        }
    }
}

void GameManager::updateMenu() {
}

void GameManager::updatePlaying() {
}

void GameManager::updateGameOver() {
}

void GameManager::render() {
}

void GameManager::resetGame() {
}
