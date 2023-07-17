#include "SystemManager.hpp"

SystemManager::SystemManager() :
    m_window(sf::VideoMode(WIDTH, HEIGHT), "Solar System"),
    m_isRunning(true)
{
    m_window.setVerticalSyncEnabled(true);
    m_systemState = SystemState::MENU;
    m_selectedOption = 0;
    if(!m_starsTexture.loadFromFile(TEXTURE_DIR + std::string("stars.jpg"))) {
        std::cout << "Error: Unnable to open background image.\n";
    }
    m_backgroundSprite.setTexture(m_starsTexture);

    // Load of planet textures and moon
    sf::Texture t;
    t.loadFromFile(TEXTURE_DIR + std::string("sun.png"));
    m_textures.push_back(t);
    t.loadFromFile(TEXTURE_DIR + std::string("mercury.png"));
    m_textures.push_back(t);
    t.loadFromFile(TEXTURE_DIR + std::string("venus.png"));
    m_textures.push_back(t);
    t.loadFromFile(TEXTURE_DIR + std::string("earth.png"));
    m_textures.push_back(t);
    t.loadFromFile(TEXTURE_DIR + std::string("jupiter.png"));
    m_textures.push_back(t);
    t.loadFromFile(TEXTURE_DIR + std::string("saturn.png"));
    m_textures.push_back(t);
    t.loadFromFile(TEXTURE_DIR + std::string("uranus.png"));
    m_textures.push_back(t);
    t.loadFromFile(TEXTURE_DIR + std::string("neptune.png"));
    m_textures.push_back(t);
    t.loadFromFile(TEXTURE_DIR + std::string("moon.png"));
    m_textures.push_back(t);

    loadFonts();
    setTexts();
}

SystemManager::~SystemManager() {
}

void SystemManager::run() {
    while(m_isRunning) {
        processEvents();
        render();
    }
    m_window.close();
}

void SystemManager::processEvents() {
    sf::Event event;
    while(m_window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            m_isRunning = false;
        } else if(event.type == sf::Event::KeyPressed) {
            if(m_systemState == SystemState::MENU) {
                handleMenuInput(event.key.code);
            } else if(m_systemState == SystemState::SIMULATION) {
                handleSimulationInput(event.key.code);
            }
        }
    }
}

void SystemManager::render() {
    m_window.clear();
    if(m_systemState == SystemState::MENU) {
        m_window.draw(m_backgroundSprite);
        drawMenu();
    } else if(m_systemState == SystemState::SIMULATION) {
        m_window.draw(m_backgroundSprite);
        drawSimulation();
    }
    m_window.display();
}

void SystemManager::handleMenuInput(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::Up) {
        m_selectedOption = (m_selectedOption - 1 + 2) % 2;
    } else if(key == sf::Keyboard::Down) {
        m_selectedOption = (m_selectedOption + 1) % 2;
    } else if(key == sf::Keyboard::Enter) {
        if(m_selectedOption == 0) {
            loadPlanets();
            m_systemState = SystemState::SIMULATION;
        } else if(m_selectedOption == 1) {
            m_isRunning = false;
        }
    }
}

void SystemManager::handleSimulationInput(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::Escape) {
        clearSimulation();
        m_systemState = SystemState::MENU;
    }
}

void SystemManager::updateMenu() {
    sf::Color white = sf::Color::White;
    sf::Color yellow = sf::Color::Yellow;
    switch(m_selectedOption) {
        case 0:
            m_startText.setFillColor(yellow);
            m_quitText.setFillColor(white);
            break;
        case 1:
            m_startText.setFillColor(white);
            m_quitText.setFillColor(yellow);
            break;
        default:
            break;
    }
}

void SystemManager::updateSimulation() {
    for(size_t i = 0; i < m_planets.size(); ++i) {
        m_planets.at(i).orbit();
    }
}

void SystemManager::drawMenu() {
    updateMenu();
    m_window.draw(m_startText);
    m_window.draw(m_quitText);
}

void SystemManager::drawSimulation() {
    updateSimulation();
    for(size_t i = 0; i < m_planets.size(); ++i) {
        sf::CircleShape planet = m_planets.at(i).getShape();
        planet.setTexture(&(m_textures.at(i)));
        m_window.draw(planet);
        std::vector<Planet> moons = m_planets.at(i).getMoons();
        for(size_t j = 0; j < moons.size(); ++j) {
            sf::CircleShape moon = moons.at(j).getShape();
            moon.setTexture(&m_textures.at(j+1));
            m_window.draw(moon);
        }
    }
}

void SystemManager::clearSimulation() {
    m_planets.clear();
}

void SystemManager::loadFonts() {
    std::string fontFile = FONT_DIR + std::string("retroGaming.ttf");
    if(!m_font.loadFromFile(fontFile)) {
        std::cout << "Error: Unnable to load font file " << fontFile << std::endl;
    }
}

void SystemManager::setTexts() {
    int menuElements = 2;
    int charSize = 30;
    sf::Color charColor = sf::Color::White;
    int offset = 20;
    int posX = 0, posY = 0;

    m_startText.setFont(m_font);
    m_startText.setString("Start simulation");
    m_startText.setCharacterSize(charSize);
    m_startText.setFillColor(charColor);
    sf::FloatRect bounds = m_startText.getLocalBounds();
    posX = (WIDTH - bounds.width)/2.f;
    posY = (HEIGHT- bounds.height * menuElements)/2.f;
    m_startText.setPosition(posX, posY);

    m_quitText.setFont(m_font);
    m_quitText.setString("Quit");
    m_quitText.setCharacterSize(charSize);
    m_quitText.setFillColor(charColor);
    bounds = m_quitText.getLocalBounds();
    posX = (WIDTH - bounds.width)/2.f;
    posY += bounds.height + offset;
    m_quitText.setPosition(posX, posY);
}

void SystemManager::loadPlanets() {
    Planet sun(50, 0);
    sun.spawnMoons(4);
    m_planets.push_back(sun);
}
