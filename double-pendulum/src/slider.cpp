#include "../include/slider.hpp"

Slider::Slider(float width, float minVal, float maxVal) : width(width), minVal(minVal), maxVal(maxVal)
{
    slider.setSize(sf::Vector2f(width, 10.0f));
    slider.setFillColor(sf::Color::Blue);
    slider.setOutlineColor(sf::Color::White);
    slider.setOutlineThickness(1.0f);

    handle.setRadius(10.0f);
    handle.setFillColor(sf::Color::Red);
    handle.setOutlineColor(sf::Color::White);
    handle.setOutlineThickness(1.0f);

    this->text.setString("");
    updateHandlePosition();
}

Slider::~Slider()
{
}

void Slider::setPosition(float x, float y)
{
    slider.setPosition(x, y);
    updateHandlePosition();
}

void Slider::setSize(float newWidth)
{
    width = newWidth;
    slider.setSize(sf::Vector2f(width, 10.0f));
    updateHandlePosition();
}

void Slider::draw(sf::RenderWindow &window)
{
    window.draw(text);
    window.draw(slider);
    window.draw(handle);
}

void Slider::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (handle.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            {
                dragging = true;
                dragOffset = event.mouseButton.x - handle.getPosition().x;
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            dragging = false;
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        if (dragging)
        {
            float newX = event.mouseMove.x - dragOffset;
            if (newX < slider.getPosition().x)
            {
                newX = slider.getPosition().x;
            }
            else if (newX > slider.getPosition().x + width)
            {
                newX = slider.getPosition().x + width;
            }
            handle.setPosition(newX, handle.getPosition().y);
        }
    }
}

float Slider::getValue()
{
    float sliderRange = maxVal - minVal;
    float position = handle.getPosition().x - slider.getPosition().x;
    float percentage = position / width;
    return minVal + sliderRange * percentage;
}

void Slider::setFont(const sf::Font &font)
{
    this->font = font;
    text.setFont(font);
}

void Slider::setText(const std::string &text)
{
    this->text.setString(text);
    this->text.setCharacterSize(20);
    this->text.setFillColor(sf::Color::Black);
    this->text.setPosition(slider.getPosition().x, slider.getPosition().y - 30.0f);
}

void Slider::updateHandlePosition()
{
    handle.setPosition(slider.getPosition().x, slider.getPosition().y - handle.getRadius());
}
