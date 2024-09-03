#include "../include/menu.hpp"
#include "../include/utils.hpp"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <vector>

enum class SimulationState
{
    MENU,
    RUNNING_SIMULATION,
    ENETERING_NUM_CIRCLES,
    EXIT
};

int main()
{
    SimulationState state = SimulationState::MENU;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Physics Simulation");
    window.setVerticalSyncEnabled(true);
    sf::Clock clock; // Starts the clock

    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<Circle> circles(NUM_CIRCLES);

    for (std::size_t i = 0; i < circles.size(); ++i)
    {
        float x = std::rand() % (WIDTH - RADIUS);
        float y = std::rand() % (HEIGHT - RADIUS);
        circles[i] = Circle(RADIUS, sf::Color::Blue, sf::Vector2f(x, y));
        circles[i].set_velocity(sf::Vector2f(std::rand() % NUM_CIRCLES - 100, std::rand() % NUM_CIRCLES - 100));
    }

    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/arial.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
    }

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(WIDTH / 2 - 100, HEIGHT / 2 - 50);

    std::string circleCountStr;

    Menu menu;

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time deltaTime = clock.restart(); // Restart clock and get deltaTime
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    if (state == SimulationState::MENU)
                    {
                        menu.move_up();
                    }
                    break;
                case sf::Keyboard::Down:
                    if (state == SimulationState::MENU)
                    {
                        menu.move_down();
                    }
                    break;
                case sf::Keyboard::Return:
                    if (state == SimulationState::MENU)
                    {
                        switch (menu.get_selected_item_index())
                        {
                        case 0:
                            state = SimulationState::RUNNING_SIMULATION;
                            for (std::size_t i = 0; i < circles.size(); ++i)
                            {
                                float x = std::rand() % (WIDTH - RADIUS);
                                float y = std::rand() % (HEIGHT - RADIUS);
                                circles[i] = Circle(RADIUS, sf::Color::Blue, sf::Vector2f(x, y));
                            }
                            break;
                        case 1:
                            state = SimulationState::ENETERING_NUM_CIRCLES;
                            circleCountStr.clear(); // Clear previous input
                            inputText.setString("Enter number of circles: ");
                            break;
                        case 2:
                            state = SimulationState::EXIT;
                            window.close();
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                case sf::Keyboard::M:
                    state = SimulationState::MENU;
                    break;
                default:
                    break;
                }
                break;
            case sf::Event::TextEntered:
                if (state == SimulationState::ENETERING_NUM_CIRCLES)
                {
                    if (event.text.unicode >= '0' && event.text.unicode <= '9')
                    {
                        circleCountStr += static_cast<char>(event.text.unicode);
                        inputText.setString("Enter number of circles: " + circleCountStr);
                    }
                    else if (event.text.unicode == '\b' && !circleCountStr.empty())
                    {
                        circleCountStr.pop_back();
                        inputText.setString("Enter number of circles: " + circleCountStr);
                    }
                    else if (event.text.unicode == '\r')
                    {
                        if (!circleCountStr.empty())
                        {
                            int numCircles = std::stoi(circleCountStr);
                            circles.resize(numCircles);

                            for (std::size_t i = 0; i < circles.size(); ++i)
                            {
                                float x = std::rand() % (WIDTH - RADIUS);
                                float y = std::rand() % (HEIGHT - RADIUS);
                                circles[i] = Circle(RADIUS, sf::Color::Blue, sf::Vector2f(x, y));
                                circles[i].set_velocity(
                                    sf::Vector2f(std::rand() % NUM_CIRCLES - 100, std::rand() % NUM_CIRCLES - 100));
                            }
                            state = SimulationState::RUNNING_SIMULATION;
                        }
                    }
                }
            default:
                break;
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        if (state == SimulationState::RUNNING_SIMULATION)
        {
            for (std::size_t i = 0; i < circles.size(); ++i)
            {
                circles[i].update(deltaTime.asSeconds());

                // Check for collisions with other circles
                for (std::size_t j = i + 1; j < circles.size(); ++j)
                {
                    collide(circles[i], circles[j]);
                }
                circles[i].draw(window);
            }
        }
        else if (state == SimulationState::MENU)
        {
            for (std::size_t i = 0; i < circles.size(); ++i)
            {
                circles[i].update_without_gravity(deltaTime.asSeconds());
                for (std::size_t j = i + 1; j < circles.size(); ++j)
                {
                    collide(circles[i], circles[j]);
                }
                circles[i].draw(window);
            }
            menu.draw(window);
        }
        else if (state == SimulationState::ENETERING_NUM_CIRCLES)
        {
            window.draw(inputText);
        }
        window.display();
    }

    return 0;
}
