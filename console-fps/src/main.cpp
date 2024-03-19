#include <ncurses.h>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include "../include/params.hpp"
#include "../include/utils.hpp"

int main()
{
    initialize_map(map);

    if (!initialize_ncurses())
    {
        endwin();
        return 1;
    }

    getmaxyx(stdscr, screenHeight, screenWidth);

    while (!quit)
    {
        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();

        switch (input = getch())
        {
        case KEY_LEFT:
            playerA -= 0.8f * fElapsedTime;
            break;
        case KEY_RIGHT:
            playerA += 0.8f * fElapsedTime;
            break;
        case KEY_UP:
            playerX += sinf(playerA) * 5.0f * fElapsedTime;
            playerY += cosf(playerA) * 5.0f * fElapsedTime;
            if (map[(int)playerY * mapWidth + (int)playerX] == '#')
            {
                playerX -= sinf(playerA) * 5.0f * fElapsedTime;
                playerY -= cosf(playerA) * 5.0f * fElapsedTime;
            }
            break;
        case KEY_DOWN:
            playerX -= sinf(playerA) * 5.0f * fElapsedTime;
            playerY -= cosf(playerA) * 5.0f * fElapsedTime;
            if (map[(int)playerY * mapWidth + (int)playerX] == '#')
            {
                playerX += sinf(playerA) * 5.0f * fElapsedTime;
                playerY += cosf(playerA) * 5.0f * fElapsedTime;
            }
            break;
        case 'q':
            quit = true;
            break;
        default:
            break;
        }

        for (int x = 0; x < screenWidth; ++x)
        {
            // for each column, calculate the projected ray angle into world space
            float rayAngle = (playerA - FOV / 2.0f) + ((float)x / (float)screenWidth) * FOV;

            float distanceToWall = 0.0f;
            bool hitWall = false;
            bool boundary = false;

            while (!hitWall && distanceToWall < depth)
            {
                distanceToWall += 0.1f;
                float eyeX = sinf(rayAngle);
                float eyeY = cosf(rayAngle);
                int testX = (int)(playerX + eyeX * distanceToWall);
                int testY = (int)(playerY + eyeY * distanceToWall);
                // test if ray is out of bounds
                if (testX < 0 || testX >= mapWidth || testY < 0 || testY >= mapHeight)
                {
                    hitWall = true;
                    distanceToWall = depth;
                }
                else
                {
                    // ray is inbounds so test to see if the ray cell is a wall block
                    if (map[testY * mapWidth + testX] == '#')
                    {
                        hitWall = true;
                        std::vector<std::pair<float, float>> p; // distance, dot
                        for (int tx = 0; tx < 2; ++tx)
                            for (int ty = 0; ty < 2; ++ty)
                            {
                                float vy = (float)testY + ty - playerY;
                                float vx = (float)testX + tx - playerX;
                                float d = sqrt(vx * vx + vy * vy);
                                float dot = (eyeX * vx / d) + (eyeY * vy / d);
                                p.push_back(std::make_pair(d, dot));
                            }
                        // sort pairs from closest to farthest
                        std::sort(p.begin(), p.end(), [](const std::pair<float, float> &left, const std::pair<float, float> &right)
                                  { return left.first < right.first; });
                        float fBound = 0.01;
                        if (acos(p.at(0).second) < fBound)
                            boundary = true;
                        if (acos(p.at(1).second) < fBound)
                            boundary = true;
                        if (acos(p.at(2).second) < fBound)
                            boundary = true;
                    }
                }
            }
            // calculate distance to ceiling and floor
            int ceiling = (float)(screenHeight / 2.0) - screenHeight / ((float)distanceToWall);
            int floor = screenHeight - ceiling;

            short shade = ' ';
            if (distanceToWall <= depth / 4.0f)
            {
                shade = '#';
            }
            else if (distanceToWall < depth / 3.0f)
            {
                shade = '@';
            }
            else if (distanceToWall < depth / 2.0f)
            {
                shade = 'X';
            }
            else if (distanceToWall < depth)
            {
                shade = '+';
            }
            else
            {
                shade = ' ';
            }

            if (boundary)
            {
                shade = ' ';
            }

            for (int y = 0; y < screenHeight; ++y)
            {
                if (y <= ceiling)
                {
                    attron(COLOR_PAIR(1));
                    mvwaddch(stdscr, y, x, ' ');
                }
                else if (y > ceiling && y <= floor)
                {
                    attron(COLOR_PAIR(2));
                    mvwaddch(stdscr, y, x, shade);
                }
                else
                {
                    attron(COLOR_PAIR(3));
                    mvwaddch(stdscr, y, x, ' ');
                }
            }
        }
        attron(COLOR_PAIR(4));
        for(int nx = 0; nx < mapWidth; ++nx)
        {
            for(int ny = 0; ny < mapHeight; ++ny)
            {
                mvwaddch(stdscr, ny, nx, map[ny * mapWidth + nx]);
            }
        }
        mvwaddch(stdscr, (int)playerY, (int)playerX, 'P');
        refresh();
        napms(1000 / 30);   // 30 fps
        tp2 = std::chrono::system_clock::now();
    }
    endwin();
    return 0;
}