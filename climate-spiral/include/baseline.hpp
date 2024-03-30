#ifndef BASELINE_HPP
#define BASELINE_HPP

#include "constants.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>
#include <vector>

class Baseline
{
  public:
    Baseline();
    ~Baseline();
    void draw(sf::RenderWindow &window);

  private:
    std::vector<float> radius;
    std::vector<float> thickness;
    std::vector<sf::Color> color;
    sf::Font font;
    std::vector<sf::CircleShape> circles;
    std::vector<std::string> months;
};

#endif