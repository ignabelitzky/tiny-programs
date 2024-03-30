#include "../include/baseline.hpp"
#include "../include/utils.hpp"

int main()
{
    std::string filename;
    std::vector<std::vector<float>> data;
    std::vector<std::string> labels;
    filename = "resources/Land-Ocean-Global-Means.csv";
    load_data_from_file(filename, data, labels);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Climate Spiral");
    Baseline baseline;
    sf::Font font;
    font.loadFromFile("resources/arial-font/arial.ttf");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();

        baseline.draw(window);
        float mappedValue = map(data[0].at(12), -1.0f, 1.0f, 0.0f, ONE_RADIUS);
        sf::Vector2f startPoint(SCREEN_WIDTH / 2 + mappedValue,
                                SCREEN_HEIGHT / 2 + mappedValue * sin(0 * 30 * M_PI / 180));
        sf::Text title;
        title.setFont(font);
        title.setCharacterSize(32);
        title.setFillColor(sf::Color::White);
        title.setString("Land Ocean Global Means (1880 - 2023)");
        title.setPosition(SCREEN_WIDTH / 2 - title.getGlobalBounds().width / 2, 5.0f); // Center the title (x-axis
        window.draw(title);
        window.display();
        sf::Vertex line[2];

        for (auto year : data)
        {
            for (size_t month = 1; month < 13; ++month)
            {
                mappedValue = map(year.at(month), -1.0f, 1.0f, 0.0f, ONE_RADIUS);
                line[0].position = startPoint;
                line[0].color = sf::Color::White;
                line[1].position = sf::Vector2f(SCREEN_WIDTH / 2 + mappedValue * cos((month - 1) * 30 * M_PI / 180),
                                                SCREEN_HEIGHT / 2 + mappedValue * sin((month - 1) * 30 * M_PI / 180));
                line[1].color = sf::Color::White;
                startPoint = line[1].position;
                window.draw(line, 2, sf::Lines);
                sf::sleep(sf::milliseconds(50));
                window.display();
            }
        }
    }
    return 0;
}