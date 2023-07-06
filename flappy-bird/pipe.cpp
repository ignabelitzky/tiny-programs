#include "pipe.h"

static int genRandomNumber(int min, int max) {
    // Obtain a random seed using the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create a random number generator engine
    std::default_random_engine generator(std::rand());

    // Create a distribution to define the range
    std::uniform_int_distribution<int> distribution(min, max);

    // Generate and return a random number within the range
    return distribution(generator);
}

Pipe::Pipe(sf::Vector2f position) {
    m_position = position;
    m_width = genRandomNumber(5, 30);
    m_height = genRandomNumber(5, height - 30);
    m_pipe.setSize(sf::Vector2f(m_width, m_height));
    m_pipe.setPosition(m_position);
    m_pipe.setOrigin(m_width/2, m_height/2);
    m_speed = 0.f;
}

Pipe::Pipe(float width, float height, sf::Vector2f position) {
    m_position = position;
    m_width = width;
    m_height = height;
    m_pipe.setSize(sf::Vector2f(m_width, m_height));
    m_pipe.setPosition(m_position);
    m_pipe.setOrigin(m_width/2, m_height/2);
    m_speed = 0.f;
}

Pipe::~Pipe() {
}

void Pipe::update() {
    m_position.x -= 10.f;
    m_pipe.setPosition(m_position);
}

void Pipe::show(sf::RenderWindow& window) {
    window.draw(m_pipe);
}
