#include "GameManager.hpp"

GameManager::GameManager() : m_window(sf::VideoMode(windowWidth, windowHeight), "Sonic"), m_isRunning(true),
    m_player(sf::Vector2f(sonicXPos, sonicYPos), groundLevel, skyLevel), m_score(0) {
    m_window.setVerticalSyncEnabled(true);

    if(!m_font.loadFromFile("./assets/fonts/retroGaming.ttf")) {
        std::cout << "Error loading the font for the score.\n";
    }
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(50);
    m_scoreText.setFillColor(sf::Color::Yellow);

    m_maxScore = retrieveMaxScore();
    m_limitSeconds = getRandomFloat(1.f, 2.f);
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

// Update game logic here
void GameManager::update() {
    m_enemyElapsed = m_enemyClock.getElapsedTime();
    if(m_enemyElapsed.asSeconds() >= m_limitSeconds) {
        Enemy enemy(sf::Vector2f(windowWidth + (enemyRadius*2), windowHeight-75));
        m_enemies.push_back(enemy);

        m_enemyClock.restart();
        m_limitSeconds = getRandomFloat(1.5f, 3.0f);
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
        m_score = 0;
    }
}

void GameManager::render() {
    m_window.clear();

    std::cout << "Score: " << m_score << std::endl;
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

    m_window.display();
}
