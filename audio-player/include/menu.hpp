#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <vector>
#include <string>
#include <stdexcept>

class Menu {
    public:
        Menu(std::vector<std::string> items);
        Menu(std::string title, std::vector<std::string> items);
        ~Menu();
        std::string show();
    private:
        const int MENU_ITEM_HEIGHT_FACTOR = 2;
        const int MENU_ITEM_PADDING = 10;
        WINDOW *menuWin;
        std::string winTitle;
        std::vector<std::string> menuItems;
        int selectedItem;
        int height, width, start_y, start_x;
        void calculate_window_dimensions();
        int longest_menu_item();
        void initialise(std::string title, std::vector<std::string> items);
        void print_menu();
};

#endif