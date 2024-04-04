#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <SFML/Graphics.hpp>

class Slider
{
  public:
    Slider(float width, float minVal, float maxVal);
    ~Slider();
    void setPosition(float x, float y);
    void setSize(float newWidth);
    void draw(sf::RenderWindow &window);
    void handleEvent(const sf::Event &event);
    float getValue();
    void setFont(const sf::Font &font);
    void setText(const std::string &text);

  private:
    sf::Font font;
    sf::Text text;
    sf::RectangleShape slider;
    sf::CircleShape handle;
    float width;
    float minVal;
    float maxVal;
    bool dragging = false;
    float dragOffset;

    void updateHandlePosition();
};

#endif