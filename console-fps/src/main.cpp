#include <ncurses.h>
#include <string>
#include <cmath>
#include <chrono>
#include <vector>
#include <utility>
#include <algorithm>

float fPlayerX = 8.0f;
float fPlayerY = 8.0f;
float fPlayerA = 0.0f;

int nScreenWidth = 0;
int nScreenHeight = 0;

int nMapHeight = 16;
int nMapWidth = 16;

float fFOV = 3.14159 / 4.0;
float fDepth = 16.0f;

std::wstring map;

int main()
{
    map += L"################";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#...........#..#";
    map += L"#...........#..#";
    map += L"#....########..#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#.......########";
    map += L"#..............#";
    map += L"#..............#";
    map += L"################";

    // WINDOW *minimap = nullptr;
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_WHITE);
    init_pair(4, COLOR_BLACK, COLOR_GREEN);
    setlocale(LC_ALL, "");
    getmaxyx(stdscr, nScreenHeight, nScreenWidth);
    noecho();
    curs_set(0);
    nodelay(stdscr, true);
    keypad(stdscr, true);
    // minimap = newwin(nMapHeight, nMapWidth, 0, 0);
    int input = 0;

    auto tp1 = std::chrono::system_clock::now();
    auto tp2 = std::chrono::system_clock::now();

    while (1)
    {
        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();

        switch (input = getch())
        {
        case KEY_LEFT:
            fPlayerA -= 0.8f * fElapsedTime;
            break;
        case KEY_RIGHT:
            fPlayerA += 0.8f * fElapsedTime;
            break;
        case KEY_UP:
            fPlayerX += sinf(fPlayerA) * 5.0f * fElapsedTime;
            fPlayerY += cosf(fPlayerA) * 5.0f * fElapsedTime;
            if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#')
            {
                fPlayerX -= sinf(fPlayerA) * 5.0f * fElapsedTime;
                fPlayerY -= cosf(fPlayerA) * 5.0f * fElapsedTime;
            }
            break;
        case KEY_DOWN:
            fPlayerX -= sinf(fPlayerA) * 5.0f * fElapsedTime;
            fPlayerY -= cosf(fPlayerA) * 5.0f * fElapsedTime;
            if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#')
            {
                fPlayerX += sinf(fPlayerA) * 5.0f * fElapsedTime;
                fPlayerY += cosf(fPlayerA) * 5.0f * fElapsedTime;
            }
            break;
        default:
            break;
        }

        for (int x = 0; x < nScreenWidth; ++x)
        {
            // for each column, calculate the projected ray angle into world space
            float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;

            float fDistanceToWall = 0.0f;
            bool bHitWall = false;
            bool bBoundary = false;

            float fEyeX = sinf(fRayAngle); // unit vector for ray in player space
            float fEyeY = cosf(fRayAngle); // unit vector for ray in player space

            while (!bHitWall && fDistanceToWall < fDepth)
            {
                fDistanceToWall += 0.1f;
                float fEyeX = sinf(fRayAngle);
                float fEyeY = cosf(fRayAngle);
                int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
                int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);
                // test if ray is out of bounds
                if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
                {
                    bHitWall = true;
                    fDistanceToWall = fDepth;
                }
                else
                {
                    // ray is inbounds so test to see if the ray cell is a wall block
                    if (map[nTestY * nMapWidth + nTestX] == '#')
                    {
                        bHitWall = true;
                        std::vector<std::pair<float, float>> p; // distance, dot
                        for (int tx = 0; tx < 2; ++tx)
                            for (int ty = 0; ty < 2; ++ty)
                            {
                                float vy = (float)nTestY + ty - fPlayerY;
                                float vx = (float)nTestX + tx - fPlayerX;
                                float d = sqrt(vx * vx + vy * vy);
                                float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
                                p.push_back(std::make_pair(d, dot));
                            }
                        // sort pairs from closest to farthest
                        std::sort(p.begin(), p.end(), [](const std::pair<float, float> &left, const std::pair<float, float> &right)
                                  { return left.first < right.first; });
                        float fBound = 0.01;
                        if (acos(p.at(0).second) < fBound)
                            bBoundary = true;
                        if (acos(p.at(1).second) < fBound)
                            bBoundary = true;
                        if (acos(p.at(2).second) < fBound)
                            bBoundary = true;
                    }
                }
            }
            // calculate distance to ceiling and floor
            int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
            int nFloor = nScreenHeight - nCeiling;

            short nShade = ' ';
            if (fDistanceToWall <= fDepth / 4.0f)
            {
                nShade = '@';
            }
            else if (fDistanceToWall < fDepth / 3.0f)
            {
                nShade = '$';
            }
            else if (fDistanceToWall < fDepth / 2.0f)
            {
                nShade = '?';
            }
            else if (fDistanceToWall < fDepth)
            {
                nShade = '~';
            }
            else
            {
                nShade = ' ';
            }

            if (bBoundary)
            {
                nShade = ' ';
            }

            for (int y = 0; y < nScreenHeight; ++y)
            {
                if (y < nCeiling)
                {
                    attron(COLOR_PAIR(1));
                    mvwaddch(stdscr, y, x, ' ');
                }
                else if (y > nCeiling && y <= nFloor)
                {
                    attron(COLOR_PAIR(2));
                    mvwaddch(stdscr, y, x, nShade);
                }
                else
                {
                    attron(COLOR_PAIR(3));
                    mvwaddch(stdscr, y, x, '.');
                }
            }
        }
        attron(COLOR_PAIR(4));
        for(int nx = 0; nx < nMapWidth; ++nx)
        {
            for(int ny = 0; ny < nMapHeight; ++ny)
            {
                mvwaddch(stdscr, ny, nx, map[ny * nMapWidth + nx]);
            }
        }
        mvwaddch(stdscr, (int)fPlayerY, (int)fPlayerX, 'P');
        mvwaddstr(stdscr, nMapHeight, 0, std::to_string(fPlayerX).c_str());
        mvwaddstr(stdscr, nMapHeight + 1, 0, std::to_string(fPlayerY).c_str());
        refresh();
        napms(1000 / 30);
        tp2 = std::chrono::system_clock::now();
    }
    endwin();
    return 0;
}