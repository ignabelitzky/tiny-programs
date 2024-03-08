#include <sstream>
#include "../include/message_box.hpp"

namespace {
    std::vector<std::string> split(const std::string &s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
}

MessageBox::MessageBox(std::string title, std::string message, std::vector<std::string> options) {
    initialize(title, message, options);
}

MessageBox::MessageBox(std::string message, std::vector<std::string> options) {
    initialize("", message, options);
}

MessageBox::~MessageBox() {
    wclear(messageBoxWin);
    wrefresh(messageBoxWin);
    delwin(messageBoxWin);
    endwin();
}

std::string MessageBox::show() {
    int key;
    while(true) {
        print_dialog_box();
        key = wgetch(messageBoxWin);
        switch(key) {
            case KEY_LEFT:
                selectedOption--;
                if(selectedOption == -1) {
                    selectedOption = winOptions.size() - 1;
                }
                break;
            case KEY_RIGHT:
                selectedOption++;
                if(selectedOption == static_cast<int>(winOptions.size())) {
                    selectedOption = 0;
                }
                break;
            case 10:
                return winOptions.at(selectedOption);
        }
    }
}

void MessageBox::initialize(std::string title, std::string message, std::vector<std::string> options) {
    initscr();
    noecho();
    curs_set(0);
    winTitle = title;
    winMessage = message;
    winOptions = options;
    selectedOption = 0;
    calculate_window_dimensions();
    messageBoxWin = newwin(height, width, start_y, start_x);
    keypad(messageBoxWin, TRUE);
    box(messageBoxWin, 0, 0);
}

void MessageBox::calculate_window_dimensions() {
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    width = maxx / 3;
    height = maxy / 4;

    start_y = (maxy - height) / 2;
    start_x = (maxx - width) / 2;

    if(!fit_options()) {
        endwin();
        throw std::runtime_error("The options do not fit in the message box");
    }
    if(!fit_message()) {
        endwin();
        throw std::runtime_error("The message does not fit in the message box");
    }

}

bool MessageBox::fit_options() {
    bool fit = true;
    int optionsLineLength = OPTIONS_HORIZONTAL_PADDING * winOptions.size();
    for(int i = 0; i < static_cast<int>(winOptions.size()); ++i) {
        optionsLineLength += winOptions.at(i).length();
    }
    fit = optionsLineLength < width;
    return fit;
}

bool MessageBox::fit_message() {
    std::vector<std::string> lines = split(winMessage, '\n');
    bool fit = true;
    for(int i = 0; i < static_cast<int>(lines.size()); ++i) {
        if(static_cast<int>(lines.at(i).length()) > width - MESSAGE_PADDING * 2) {
            fit = false;
            break;
        }
    }
    if(fit) {
        if(static_cast<int>(lines.size()) > height - MESSAGE_PADDING * 2 - OPTIONS_VERTICAL_PADDING * 2 - 1) {
            fit = false;
        }
    }
    return fit;
}


int MessageBox::options_length() {
    int optionsLength = 0;
    for(int i = 0; i < static_cast<int>(winOptions.size()); ++i) {
        optionsLength += winOptions.at(i).length();
    }
    return optionsLength;
}

void MessageBox::print_dialog_box() {
    wclear(messageBoxWin);
    box(messageBoxWin, 0, 0);
    int y = 0;
    int x = (width - winTitle.length()) / 2;
    mvwprintw(messageBoxWin, y, x, winTitle.c_str());
    y = MESSAGE_PADDING;
    x = MESSAGE_PADDING;
    for(int i = 0; i < static_cast<int>(winMessage.size()); ++i) {
        if(winMessage.at(i) == '\n') {
            y++;
            x = MESSAGE_PADDING;
            continue;
        }
        mvwaddch(messageBoxWin, y, x, winMessage.at(i));
        ++x;
    }

    y = height - OPTIONS_VERTICAL_PADDING - 2;
    x = winOptions.size() * OPTIONS_HORIZONTAL_PADDING * 2 - 1;
    x += options_length();
    x = (width - x) / 2;

    for(int i = 0; i < static_cast<int>(winOptions.size()); ++i) {
        i == selectedOption ? wattron(messageBoxWin, A_REVERSE) : wattroff(messageBoxWin, A_REVERSE);
        mvwprintw(messageBoxWin, y, x, winOptions.at(i).c_str());
        x += winOptions.at(i).length() + OPTIONS_HORIZONTAL_PADDING * 2;
    }
    wattroff(messageBoxWin, A_REVERSE);
    wrefresh(messageBoxWin);
}