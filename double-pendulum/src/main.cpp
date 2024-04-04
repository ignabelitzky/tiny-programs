#include "../include/pendulum.hpp"
#include "../include/slider.hpp"
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> texts = {"Mass One", "Mass Two", "Length One", "Length Two", "Time Step"};

    Pendulum pendulum;

    Slider massOneSlider(100.0f, 10.0f, 100.0f);
    Slider massTwoSlider(100.0f, 10.0f, 100.0f);
    Slider lengthOneSlider(100.0f, 50.0f, 600.0f);
    Slider lengthTwoSlider(100.0f, 50.0f, 600.0f);
    Slider timeSlider(100.0f, 0.01f, 0.1f);

    massOneSlider.setPosition(40.0f, 50.0f);
    massTwoSlider.setPosition(40.0f, 100.0f);
    lengthOneSlider.setPosition(40.0f, 150.0f);
    lengthTwoSlider.setPosition(40.0f, 200.0f);
    timeSlider.setPosition(40.0f, 250.0f);

    float massOne = pendulum.getMassOne();
    float massTwo = pendulum.getMassTwo();
    float lengthOne = pendulum.getLengthOne();
    float lengthTwo = pendulum.getLengthTwo();
    float time = 0.01f;

    sf::RenderWindow window(sf::VideoMode(width, height), "Double Pendulum Simulation");

    sf::Font font;
    font.loadFromFile("resources/arial.ttf");

    massOneSlider.setText(texts[0]);
    massTwoSlider.setText(texts[1]);
    lengthOneSlider.setText(texts[2]);
    lengthTwoSlider.setText(texts[3]);
    timeSlider.setText(texts[4]);

    massOneSlider.setFont(font);
    massTwoSlider.setFont(font);
    lengthOneSlider.setFont(font);
    lengthTwoSlider.setFont(font);
    timeSlider.setFont(font);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            massOneSlider.handleEvent(event);
            massTwoSlider.handleEvent(event);
            lengthOneSlider.handleEvent(event);
            lengthTwoSlider.handleEvent(event);
            timeSlider.handleEvent(event);
            pendulum.handleEvent(event);
        }

        window.clear(sf::Color::White);

        massOne = massOneSlider.getValue();
        massTwo = massTwoSlider.getValue();
        lengthOne = lengthOneSlider.getValue();
        lengthTwo = lengthTwoSlider.getValue();
        time = timeSlider.getValue();

        pendulum.setMassOne(massOne);
        pendulum.setMassTwo(massTwo);
        pendulum.setLengthOne(lengthOne);
        pendulum.setLengthTwo(lengthTwo);

        pendulum.update(time);

        massOneSlider.draw(window);
        massTwoSlider.draw(window);
        lengthOneSlider.draw(window);
        lengthTwoSlider.draw(window);
        timeSlider.draw(window);
        pendulum.draw(window);

        window.display();
    }
    return 0;
}