#include <iostream>
#include <ncurses.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main() {

    //std::string density = "@%*+=-. '~^_:;,<ix+-?10|tfjrxnuvM@$0ZNTIt;:";
    std::string density = " .:-=+*#%@";
    //std::string density = "@%#*+=-:. ";
    //std::string density = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,^`. ";

    cv::VideoCapture cap(0);
    cv::Mat frame;
    int videoHeight = 0, videoWidth = 0;
    int colorBlue = 0, colorGreen = 0, colorRed = 0;
    int index = 0, avgColor = 0;

    // Initialise screen
    initscr();

    // Disable input buffering
    cbreak();

    // Capture of special keys (like F1, F2, etc)
    keypad(stdscr, TRUE);

    // Don't display pressed keys
    noecho();

    nodelay(stdscr, TRUE);

    // Initialise of colors
    if(has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        attron(COLOR_PAIR(1));
    }

    // Program logic
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    move(0, 0);

    while(true) {
        cap >> frame;
        if(frame.empty()) {
            std::cout << "End of the video" << std::endl;
            break;
        }
        cv::resize(frame, frame, cv::Size(xMax, yMax));
        cv::Size sz = frame.size();
        videoWidth = sz.width;
        videoHeight = sz.height;
        for(int i = 0; i < videoHeight; ++i) {
            for(int j = 0; j < videoWidth; ++j) {
                colorBlue = frame.at<cv::Vec3b>(i, j)[0];
                colorGreen = frame.at<cv::Vec3b>(i, j)[1];
                colorRed = frame.at<cv::Vec3b>(i, j)[2];
                avgColor = (colorBlue + colorGreen + colorRed) / 3;
                index = floor(avgColor / (255 / density.size()));
                if(index >= density.size())
                index = density.size() - 1;
                addch(density.at(index));
                index = 0;
            }
            move(i+1, 0);
        }
        refresh();
        napms(33);
        int key = getch();
        if(key == 'q' || key == 'Q') {
            break;
        }
    }
    cap.release();
    getch();

    // End ncurses
    endwin();
}
