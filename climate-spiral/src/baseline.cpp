#include "../include/baseline.hpp"

Baseline::Baseline()
{
    radius = {ZERO_RADIUS, ONE_RADIUS, MONTH_RADIUS};
    thickness = {1.0f, 1.0f, 2.0f};
    color = {sf::Color::Green, sf::Color::Red, sf::Color::Yellow};
    font.loadFromFile("resources/arial-font/arial.ttf");
    for (int i = 0; i < 3; ++i)
    {
        sf::CircleShape circle(radius[i]);
        circle.setOrigin(radius[i], radius[i]);
        circle.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        circle.setOutlineThickness(thickness[i]);
        circle.setOutlineColor(color[i]);
        circle.setFillColor(sf::Color::Transparent);
        circles.push_back(circle);
    }
    months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
}

Baseline::~Baseline()
{
}

void Baseline::draw(sf::RenderWindow &window)
{
    for (auto circle : circles)
    {
        window.draw(circle);
    }
    for (int i = 0; i < 12; ++i)
    {
        sf::Text text;
        text.setFont(font);
        text.setString(months[i]);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
        text.setPosition(SCREEN_WIDTH / 2 + (MONTH_RADIUS + TEXT_OFFSET) * cos(i * 30 * M_PI / 180),
                         SCREEN_HEIGHT / 2 + (MONTH_RADIUS + TEXT_OFFSET) * sin(i * 30 * M_PI / 180));
        text.rotate(90 + i * 30);
        window.draw(text);
    }
    sf::Text text;
    text.setFont(font);
    text.setString("0 degrees");
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - (ZERO_RADIUS + TEXT_OFFSET));
    window.draw(text);
    text.setString("1 degrees");
    text.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - (ONE_RADIUS + TEXT_OFFSET));
    window.draw(text);
}