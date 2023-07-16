#include "GameManager.hpp"

GameManager::GameManager() :
    m_window(sf::VideoMode(WIDTH, HEIGHT), "Brick Race"), m_isRunning(true),
    m_gameState(GameState::MENU), m_score(0), m_selectedOption(0)
{
    m_window.setVerticalSyncEnabled(true);
    loadBackgroundMusic(std::string("background_electronicFantasy.ogg"));
    loadFonts();
    setTexts();
    m_highScore = loadHighScore(std::string("highscore.txt"));
    m_player.setPosition(WIDTH/2, HEIGHT/2);
}

GameManager::~GameManager() {
    m_backgroundMusic.stop();
}

void GameManager::run() {
    m_backgroundMusic.play();
    while(m_isRunning) {
        processEvents();
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
    if(key == sf::Keyboard::Left) {
        m_player.moveLeft();
    } else if(key == sf::Keyboard::Right) {
        m_player.moveRight();
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
        } else if(m_selectedOption == 1){
            m_isRunning = false;
        }
    }
}

void GameManager::updateMenu() {
    sf::Color white = sf::Color::White;
    sf::Color yellow = sf::Color::Yellow;
    switch(m_selectedOption) {
        case 0:
            m_startGameText.setFillColor(yellow);
            m_quitText.setFillColor(white);
            break;
        case 1:
            m_startGameText.setFillColor(white);
            m_quitText.setFillColor(yellow);
            break;
        default:
            break;
    }
    m_window.draw(m_startGameText);
    m_window.draw(m_quitText);
}

void GameManager::updatePlaying() {
    m_player.draw(m_window);
}

void GameManager::updateGameOver() {
}

void GameManager::render() {
    m_window.clear();
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
    m_window.display();
}

void GameManager::resetGame() {
}

void GameManager::loadBackgroundMusic(std::string fileName) {
    std::string musicFile = SOUND_DIR + fileName;
    if(!m_backgroundMusic.openFromFile(musicFile)) {
        std::cout << "Unnable to load music file " << fileName << std::endl;
    } else {
        m_backgroundMusic.setLoop(true);
        m_backgroundMusic.play();
    }
}

void GameManager::loadFonts() {
    std::string fontFile = FONT_DIR + std::string("retroGaming.ttf");
    if(!m_font.loadFromFile(fontFile)) {
        std::cout << "Unnable to load font file " << fontFile << std::endl;
    }
}

void GameManager::setTexts() {
    int menuElements = 2;
    int charSize = 30;
    sf::Color charColor = sf::Color::White;
    int offset = 10;

    float posX = 0;
    float posY = 0;

    m_startGameText.setFont(m_font);
    m_startGameText.setString("Start");
    m_startGameText.setCharacterSize(charSize);
    m_startGameText.setFillColor(charColor);
    sf::FloatRect bounds = m_startGameText.getLocalBounds();
    posX = (WIDTH - bounds.width)/2.f;
    posY = (HEIGHT - bounds.height * menuElements)/2.f;
    m_startGameText.setPosition(posX, posY);

    m_restartText.setFont(m_font);
    m_restartText.setString("Restart");
    m_restartText.setCharacterSize(charSize);
    m_restartText.setFillColor(charColor);
    bounds = m_restartText.getLocalBounds();
    posX = (WIDTH - bounds.width)/2.f;
    m_restartText.setPosition(posX,posY);

    m_quitText.setFont(m_font);
    m_quitText.setString("Quit");
    m_quitText.setCharacterSize(charSize);
    m_quitText.setFillColor(charColor);
    bounds = m_quitText.getLocalBounds();
    posX = (WIDTH - bounds.width)/2.f;
    posY += bounds.height + offset;
    m_quitText.setPosition(posX, posY);

    m_scoreText.setFont(m_font);
    m_scoreText.setString("Hi: " + std::to_string(m_highScore) + "\tScore: " + std::to_string(m_score));
    m_scoreText.setCharacterSize(charSize);
    m_scoreText.setFillColor(charColor);
    bounds = m_scoreText.getLocalBounds();
    posX = (WIDTH - bounds.width)/2.f;
    posY += bounds.height + offset;
    m_scoreText.setPosition(posX, posY);
}
