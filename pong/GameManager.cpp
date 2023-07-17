#include "GameManager.hpp"

GameManager::GameManager() :
    m_window(sf::VideoMode(width, height), "Pong"),
    m_isRunning(true),
    m_gameState(GameState::MENU),
    m_playerOne(paddleWidth, paddleHeight, sf::Vector2f(50.f, height / 2.f - paddleHeight / 2.f)),
    m_playerTwo(paddleWidth, paddleHeight, sf::Vector2f(width - 50.f - paddleWidth, 
                height / 2.f - paddleHeight / 2.f)), 
    m_ball(ballRadius, ballInitialPosition, ballInitialVelocity),
    m_scorePlayerOne(0), m_scorePlayerTwo(0),
    m_selectedOption(0)
{
    m_window.setVerticalSyncEnabled(true);
    loadBackgroundMusic(std::string("background_music.ogg"));
    loadFonts();
    setTexts();
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
}

void GameManager::updatePlaying() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_playerOne.getPosition().y > 0)
        m_playerOne.moveUp();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_playerOne.getPosition().y + paddleHeight < height)
        m_playerOne.moveDown();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_playerTwo.getPosition().y > 0)
        m_playerTwo.moveUp();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_playerTwo.getPosition().y + paddleHeight < height)
        m_playerTwo.moveDown();

    // update ball position
    m_ball.update();

    sf::Vector2f ballPosition = m_ball.getPosition();

    // Check for collision with paddles
    if(ballPosition.x - ballRadius < m_playerOne.getPosition().x + paddleWidth &&
            ballPosition.y + ballRadius > m_playerOne.getPosition().y &&
            ballPosition.y - ballRadius < m_playerOne.getPosition().y + paddleHeight) {
        m_ball.setVelocity(sf::Vector2f(-m_ball.getVelocity().x, m_ball.getVelocity().y));
    }
    if(ballPosition.x + ballRadius > m_playerTwo.getPosition().x &&
            ballPosition.y + ballRadius > m_playerTwo.getPosition().y &&
            ballPosition.y - ballRadius < m_playerTwo.getPosition().y + paddleHeight) {
        m_ball.setVelocity(sf::Vector2f(-m_ball.getVelocity().x, m_ball.getVelocity().y));
    }

    if(ballPosition.y + ballRadius > height || ballPosition.y - ballRadius < 0) {
        m_ball.setVelocity(sf::Vector2f(m_ball.getVelocity().x, -m_ball.getVelocity().y));
    }

    // Check for goals
    if(ballPosition.x < 0 || ballPosition.x > width) {
        resetRound();
        if(ballPosition.x < 0) {
            ++m_scorePlayerTwo;
            m_scorePlayerTwoText.setString(std::to_string(m_scorePlayerTwo));
        } else if(ballPosition.x > width) {
            ++m_scorePlayerOne;
            m_scorePlayerOneText.setString(std::to_string(m_scorePlayerOne));
        }
        if(m_scorePlayerOne == winGoal || m_scorePlayerTwo == winGoal) {
            m_gameState = GameState::GAME_OVER;
            if(m_scorePlayerOne == winGoal) {
                m_winnerText.setString("Player One wins!");
            } else {
                m_winnerText.setString("Player Two wins!");
            }
        }
    }
}

void GameManager::updateGameOverMenu() {
    sf::Color white = sf::Color::White;
    sf::Color yellow = sf::Color::Yellow;
    switch(m_selectedOption) {
        case 0:
            m_restartText.setFillColor(yellow);
            m_quitText.setFillColor(white);
            break;
        case 1:
            m_restartText.setFillColor(white);
            m_quitText.setFillColor(yellow);
            break;
        default:
            break;
    }
}

void GameManager::render() {
    m_window.clear();
    if(m_gameState == GameState::MENU) {
        drawMenu();
    } else if(m_gameState == GameState::PLAYING) {
        drawPlaying();
    } else if(m_gameState == GameState::GAME_OVER) {
        drawGameOverMenu();
    }
    m_window.display();
}

void GameManager::drawMenu() {
    updateMenu();
    m_window.draw(m_startGameText);
    m_window.draw(m_quitText);
}

void GameManager::drawPlaying() {
    updatePlaying();
    m_window.draw(m_scorePlayerOneText);
    m_window.draw(m_scorePlayerTwoText);
    m_window.draw(m_playerOne.getShape());
    m_window.draw(m_playerTwo.getShape());
    m_window.draw(m_ball.getShape());
}

void GameManager::drawGameOverMenu() {
    updateGameOverMenu();
    m_window.draw(m_winnerText);
    m_window.draw(m_restartText);
    m_window.draw(m_quitText);
}

void GameManager::resetRound() {
    m_ball.setPosition(ballInitialPosition);
    if(getRandomFloat(0.f, 1.f) < 0.5f) {
        m_ball.setVelocity(-ballInitialVelocity);
    } else {
        m_ball.setVelocity(ballInitialVelocity);
    }
}

void GameManager::resetGame() {
    m_scorePlayerOne = 0;
    m_scorePlayerTwo = 0;
    m_scorePlayerOneText.setString(std::to_string(m_scorePlayerOne));
    m_scorePlayerTwoText.setString(std::to_string(m_scorePlayerTwo));
    m_selectedOption = 0;
    m_gameState = GameState::PLAYING;
}

void GameManager::loadBackgroundMusic(std::string fileName) {
    std::string musicFile = SOUND_DIR + fileName;
    if(!m_backgroundMusic.openFromFile(musicFile)) {
        std::cout << "Error: Unnable to load music file " << fileName << std::endl;
    } else {
        m_backgroundMusic.setLoop(true);
    }
}

void GameManager::loadFonts() {
    std::string fontFile = FONT_DIR + std::string("retroGaming.ttf");
    if(!m_font.loadFromFile(fontFile)) {
        std::cout << "Error: Unnable to load font file " << fontFile << std::endl;
    }
}

void GameManager::setTexts() {
    int menuElements = 2;
    int charSize =  30;
    sf::Color charColor = sf::Color::White;
    int offset = 20;

    float posX = 0;
    float posY = 0;

    m_winnerText.setFont(m_font);
    m_winnerText.setString("Player One wins!");
    m_winnerText.setCharacterSize(charSize*2);
    m_winnerText.setFillColor(charColor);
    sf::FloatRect bounds = m_winnerText.getLocalBounds();
    posX = (width - bounds.width)/2.f;
    posY = 100;
    m_winnerText.setPosition(posX, posY);

    m_startGameText.setFont(m_font);
    m_startGameText.setString("Start");
    m_startGameText.setCharacterSize(charSize);
    m_startGameText.setFillColor(charColor);
    bounds = m_startGameText.getLocalBounds();
    posX = (width - bounds.width)/2.f;
    posY = (height - bounds.height * menuElements)/2.f;
    m_startGameText.setPosition(posX, posY);

    m_restartText.setFont(m_font);
    m_restartText.setString("Restart");
    m_restartText.setCharacterSize(charSize);
    m_restartText.setFillColor(charColor);
    bounds = m_restartText.getLocalBounds();
    posX = (width - bounds.width)/2.f;
    m_restartText.setPosition(posX, posY);

    m_quitText.setFont(m_font);
    m_quitText.setString("Quit");
    m_quitText.setCharacterSize(charSize);
    m_quitText.setFillColor(charColor);
    bounds = m_quitText.getLocalBounds();
    posX = (width - bounds.width)/2.f;
    posY += bounds.height + offset;
    m_quitText.setPosition(posX, posY);

    m_scorePlayerOneText.setFont(m_font);
    m_scorePlayerOneText.setString("0");
    m_scorePlayerOneText.setCharacterSize(charSize*2);
    m_scorePlayerOneText.setFillColor(charColor);
    m_scorePlayerOneText.setPosition(width/4, 70);

    m_scorePlayerTwoText.setFont(m_font);
    m_scorePlayerTwoText.setString("0");
    m_scorePlayerTwoText.setCharacterSize(charSize*2);
    m_scorePlayerTwoText.setFillColor(charColor);
    m_scorePlayerTwoText.setPosition((width/4)*3, 70);
}
