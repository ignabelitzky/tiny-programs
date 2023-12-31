#include "GameManager.hpp"

GameManager::GameManager() :
        m_window(sf::VideoMode(windowWidth, windowHeight), "Sonic"), m_isRunning(true),
        m_gameState(GameState::MENU), m_player(sf::Vector2f(0.f, 0.f), groundLevel, skyLevel),
        m_lives(3), m_score(0), m_selectedOption(0) {
    m_window.setVerticalSyncEnabled(true);
    m_player.setPosition(sf::Vector2f(200.f, windowHeight/2.f));

    if(!m_backgroundTexture.loadFromFile("./assets/sprites/stars.jpg")) {
        std::cout << "Error: Unnable to load background texture.\n";
    }
    m_backgroundSprite.setTexture(m_backgroundTexture);

    // load music
    loadBackgroundMusic();

    // load fonts and set texts
    loadFonts();
    setTexts();

    m_maxScore = retrieveMaxScore();

    m_limitSeconds = getRandomFloat(1.f, 2.f);
    m_cloudLimitSeconds = getRandomFloat(0.f, 2.f);
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
    m_cloudElapsed = m_cloudClock.getElapsedTime();
    if(m_cloudElapsed.asSeconds() >= m_cloudLimitSeconds) {
        Cloud cloud(sf::Vector2f(windowWidth * 2, getRandomFloat(0.5f, windowHeight / 2.0f)));
        m_clouds.push_back(cloud);
        m_cloudClock.restart();
        m_cloudLimitSeconds = getRandomFloat(0.5f, 2.0f);
    }
    for(size_t i = 0; i < m_clouds.size(); ++i) {
        m_clouds.at(i).update(0.5f);
        if(m_clouds.at(i).getPosition().x < (-windowHeight/2.f)) {
            m_clouds.erase(m_clouds.begin() + i);
            --i;
        }
    }

    m_enemyElapsed = m_enemyClock.getElapsedTime();
    if(m_enemyElapsed.asSeconds() >= m_limitSeconds) {
        Crab crab(sf::Vector2f(windowWidth + (crabRadius*2), windowHeight - crabRadius - 5.f));
        m_enemies.push_back(crab);

        m_enemyClock.restart();
        m_limitSeconds = getRandomFloat(1.0f, 2.0f);
    }

    m_player.update(0.5f);
    m_floor.update(0.5f);
    for(size_t i = 0; i < m_enemies.size(); ++i) {
        m_enemies.at(i).update(0.5f);
        if(m_enemies.at(i).getPosition().x < -crabRadius) {
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
        m_lives--;
        if(m_lives <= 0) {
            if(m_score > m_maxScore) {
                m_maxScore = m_score;
                saveMaxScore(m_maxScore);
            }
            m_gameState = GameState::GAME_OVER;
        } else {
            // Reset enemies for the next life
            m_enemies.clear();
        }
    }
}

void GameManager::updateGameOver() {
    drawGameOverMenu();
}

void GameManager::render() {
    m_window.clear();

    m_window.draw(m_backgroundSprite);
    if(m_gameState == GameState::MENU) {
        drawMenu();
    } else if(m_gameState == GameState::PLAYING) {
        sf::Texture heartTexture;
        if(!heartTexture.loadFromFile("./assets/sprites/heart.png")) {
            std::cout << "Error loading the heart texture.\n";
        }
        sf::Sprite heartSprite(heartTexture);
        const float heartSize = 75.0f;
        const float heartSpacing = 5.0f;
        const float heartsX = static_cast<float>(windowWidth) - (heartSize * 3) - (heartSpacing * 2);
        const float heartsY = 10.0f;
        for(int i = 0; i < m_lives; ++i) {
            heartSprite.setPosition(heartsX + (i * (heartSize + heartSpacing)), heartsY);
            m_window.draw(heartSprite);
        }
        m_scoreText.setString("HI: " + std::to_string(m_maxScore) + "\tScore: " + std::to_string(m_score));
        m_scoreText.setPosition(10, 10);
        std::vector<sf::Sprite> floor = m_floor.getSprites();
        for(size_t i = 0; i < m_clouds.size(); ++i) {
            m_window.draw(m_clouds.at(i).getShape());
        }
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
    scoreText.setFont(m_font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score: " + std::to_string(m_score));
    scoreText.setPosition(200.f, 400.f);
    m_window.draw(scoreText);

    sf::Text highScoreText;
    highScoreText.setFont(m_font);
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
    m_lives = 3;
    m_gameState = GameState::PLAYING;
}

void GameManager::loadBackgroundMusic() {
    if(!m_backgroundMusic.openFromFile("./assets/sounds/sonic_music.wav")) {
        std::cout << "Error loading the brackground music.\n";
    }
    m_backgroundMusic.setLoop(true);
}

void GameManager::loadFonts() {
    if(!m_font.loadFromFile("./assets/fonts/retroGaming.ttf")) {
        std::cout << "Error loading the font for the score.\n";
    }
}

void GameManager::setTexts() {
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(50);
    m_scoreText.setFillColor(sf::Color::Yellow);

    m_startGameText.setFont(m_font);
    m_startGameText.setCharacterSize(50);
    m_startGameText.setFillColor(sf::Color::White);
    m_startGameText.setString("Start Game");
    m_startGameText.setPosition(200.f, 200.f);

    m_restartText.setFont(m_font);
    m_restartText.setCharacterSize(50);
    m_restartText.setFillColor(sf::Color::White);
    m_restartText.setString("Restart Game");
    m_restartText.setPosition(200.f, 200.f);

    m_quitText.setFont(m_font);
    m_quitText.setCharacterSize(50);
    m_quitText.setFillColor(sf::Color::White);
    m_quitText.setString("Quit");
    m_quitText.setPosition(200.f, 300.f);
}
