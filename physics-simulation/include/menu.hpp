#ifndef MENU_HPP
#define MENU_HPP

#include "params.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Menu
{
  public:
    Menu();
    ~Menu();
    void draw(sf::RenderWindow &window);
    void move_up();
    void move_down();
    int get_selected_item_index();

  private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> options;
};

#endif
