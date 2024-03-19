#include "../include/utils.hpp"

void initialize_map(std::wstring &map)
{
    map += L"################";
    map += L"#              #";
    map += L"#   ####    #  #";
    map += L"#   ##     ##  #";
    map += L"#   #     ##   #";
    map += L"#        ##    #";
    map += L"#  #######     #";
    map += L"#              #";
    map += L"#        #     #";
    map += L"#        ##    #";
    map += L"#   #     ##   #";
    map += L"#   ##     ##  #";
    map += L"#              #";
    map += L"#    ###########";
    map += L"#              #";
    map += L"################";
}

bool initialize_ncurses()
{
    bool result = true;
    initscr();
    if (has_colors() == FALSE)
    {
        endwin();
        std::cout <<"Your terminal does not support color\n";
        result = false;
    } else {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLUE);
        init_pair(2, COLOR_WHITE, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_WHITE);
        init_pair(4, COLOR_BLACK, COLOR_GREEN);
    }
    setlocale(LC_ALL, "");
    noecho();
    curs_set(0);
    nodelay(stdscr, true);
    keypad(stdscr, true);
    return result;
}