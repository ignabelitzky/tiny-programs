#include "GameManager.hpp"

GameManager::GameManager() : m_window(sf::VideoMode(windowWidth, windowHeight), "Sonic"), m_isRunning(true),
    m_gameState(GameState::MENU), m_player(sf::Vector2f(sonicXPos, sonicYPos), groundLevel, skyLevel),
    m_score(0), m_selectedOption(0) {
    m_window.setVerticalSyncEnabled(true);

    // Load the background music
    if(!m_backgroundMusic.openFromFile("./assets/sounds/sonic_music.wav")) {
        std::cout << "Error loading the brackground music.\n";
    }
    m_backgroundMusic.setLoop(true);

    if(!m_font.loadFromFile("./assets/fonts/retroGaming.ttf")) {
        std::cout << "Error loading the font for the score.\n";
    }
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(50);
    m_scoreText.setFillColor(sf::Color::Yellow);

    if(!m_menuFont.loadFromFile("./assets/fonts/retroGaming.ttf")) {
        std::cout << "Error loading the font for the score.\n";
    }
    m_startGameText.setFont(m_menuFont);
    m_startGameText.setCharacterSize(50);
    m_startGameText.setFillColor(sf::Color::White);
    m_startGameText.setString("Start Game");
    m_startGameText.setPosition(200.f, 200.f);

    m_restartText.setFont(m_menuFont);
    m_restartText.setCharacterSize(50);
    m_restartText.setFillColor(sf::Color::White);
    m_restartText.setString("Restart Game");
    m_restartText.setPosition(200.f, 200.f);

    m_quitText.setFont(m_menuFont);
    m_quitText.setCharacterSize(50);
    m_quitText.setFillColor(sf::Color::White);
    m_quitText.setString("Quit");
    m_quitText.setPosition(200.f, 300.f);

    m_maxScore = retrieveMaxScore();
    m_limitSeconds = getRandomFloat(1.f, 2.f);
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
        }
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
            if(m_gameState == GameState::MENU) {
                handleMenuInput(event.key.code);
            } else if(m_gameState == GameState::GAME_OVER) {
                handleGameOverInput(event.key.code);
            } else if(m_gameState == GameState::PLAYING) {
                if(event.key.code == sf::Keyboard::Up)
                    m_player.jump();
            }
        }
    }
}

void GameManager::handleMenuInput(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::Up) {
        m_selectedOption = (m_selectedOption - 1 + 2) % 2;
    } else if(key == sf::Keyboard::Down) {
        m_selectedOption = (m_selectedOption + 1) % 2;
    } else if (key == sf::Keyboard::Enter) {
        if(m_selectedOption == 0) {
            m_gameState = GameState::PLAYING;
        } else if(m_selectedOption == 1) {
            m_isRunning = false;
        }
    }
}

void GameManager::handleGameOverInput(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::Up) {
        m_selectedOption = (m_selectedOption - 1 + 2) % 2;
    } else if(key == sf::Keyboard::Down) {
        m_selectedOption = (m_selectedOption + 1) % 2;
    } else if(key == sf::Keyboard::Enter) {
        if(m_selectedOption == 0) {
            resetGame();
        } else if(m_selectedOption == 1) {
            m_isRunning = false;
        }
    }
}

void GameManager::updateMenu() {
    drawMenu();
}

// Update game logic here
void GameManager::updatePlaying() {
    m_enemyElapsed = m_enemyClock.getElapsedTime();
    if(m_enemyElapsed.asSeconds() >= m_limitSeconds) {
        Enemy enemy(sf::Vector2f(windowWidth + (enemyRadius*2), windowHeight-75));
        m_enemies.push_back(enemy);

        m_enemyClock.restart();
        m_limitSeconds = getRandomFloat(1.0f, 2.0f);
    }

    m_player.update(0.5f);
    m_floor.update(0.5f);
    for(size_t i = 0; i < m_enemies.size(); ++i) {
        m_enemies.at(i).update(0.5f);
        if(m_enemies.at(i).getPosition().x < -enemyRadius) {
            m_enemies.erase(m_enemies.begin() + i);
            --i;
        }
    }

    // Collision detection
    bool collisionDetected = false;
    for(auto& enemy : m_enemies) {
        if(m_player.collidesWith(enemy)) {
            collisionDetected = true;
            break;
        } else if(m_player.getPosition().x > enemy.getPosition().x && !enemy.isPassed()) {
            m_score++;
            enemy.setPassed(true);
        }
    }
    if(collisionDetected) {
        if(m_score > m_maxScore) {
            m_maxScore = m_score;
            saveMaxScore(m_maxScore);
        }
        m_gameState = GameState::GAME_OVER;
    }
}

void GameManager::updateGameOver() {
    drawGameOverMenu();
}

void GameManager::render() {
    m_window.clear();

    if(m_gameState == GameState::MENU) {
        drawMenu();
    } else if(m_gameState == GameState::PLAYING) {
        m_scoreText.setString("HI: " + std::to_string(m_maxScore) + "\tScore: " + std::to_string(m_score));
        m_scoreText.setPosition(10, 10);
        std::vector<sf::Sprite> floor = m_floor.getSprites();
        for(size_t i = 0; i < floor.size(); ++i) {
            m_window.draw(floor.at(i));
        }
        for(size_t i = 0; i < m_enemies.size(); ++i) {
            m_window.draw(m_enemies.at(i).getShape());
        }
        m_window.draw(m_player.getShape());
        m_window.draw(m_scoreText);
    } else if(m_gameState == GameState::GAME_OVER) {
        drawGameOverMenu();
    }
    m_window.display();
}

void GameManager::drawMenu() {
    m_window.draw(m_startGameText);
    m_window.draw(m_quitText);

    // Highlight the selected option
    if(m_selectedOption == 0) {
        m_startGameText.setFillColor(sf::Color::Yellow);
        m_quitText.setFillColor(sf::Color::White);
    } else {
        m_startGameText.setFillColor(sf::Color::White);
        m_quitText.setFillColor(sf::Color::Yellow);
    }
}

void GameManager::drawGameOverMenu() {
    m_window.draw(m_restartText);
    m_window.draw(m_quitText);

    // Highlight the selected option
    if(m_selectedOption == 0) {
        m_restartText.setFillColor(sf::Color::Yellow);
        m_quitText.setFillColor(sf::Color::White);
    } else {
        m_restartText.setFillColor(sf::Color::White);
        m_quitText.setFillColor(sf::Color::Yellow);
    }

    // Display the score and high score
    sf::Text scoreText;
    scoreText.setFont(m_menuFont);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score: " + std::to_string(m_score));
    scoreText.setPosition(200.f, 400.f);
    m_window.draw(scoreText);

    sf::Text highScoreText;
    highScoreText.setFont(m_menuFont);
    highScoreText.setCharacterSize(30);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setString("High Score: " + std::to_string(m_maxScore));
    highScoreText.setPosition(200.f, 450.f);
    m_window.draw(highScoreText);
}

void GameManager::resetGame() {
    m_enemies.clear();
    m_score = 0;
    m_selectedOption = 0;
    m_gameState = GameState::PLAYING;
}
