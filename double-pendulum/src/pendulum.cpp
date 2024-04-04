#include "../include/pendulum.hpp"

Pendulum::Pendulum()
{
    origin = std::make_pair(width / 2.0f, height / 2.0f);
    lengthOne = 200.0f;
    lengthTwo = 200.0f;
    massOne = 20.0f;
    massTwo = 30.0f;
    angleOne = M_PI / 8.0f;
    angleTwo = M_PI / 4.0f;
    positionOne = std::make_pair(lengthOne * sin(angleOne) + origin.first, -lengthOne * cos(angleOne) + origin.second);
    positionTwo =
        std::make_pair(lengthTwo * sin(angleTwo) + positionOne.first, -lengthTwo * cos(angleTwo) + positionOne.second);
    gravity = -0.1f;
    angularVelocityOne = 0.0f;
    angularVelocityTwo = 0.0f;
    angularAccelerationOne = 0.0f;
    angularAccelerationTwo = 0.0f;
}

Pendulum::~Pendulum()
{
}

void Pendulum::setLengthOne(float length)
{
    lengthOne = length;
}

void Pendulum::setLengthTwo(float length)
{
    lengthTwo = length;
}

void Pendulum::setMassOne(float mass)
{
    massOne = mass;
}

void Pendulum::setMassTwo(float mass)
{
    massTwo = mass;
}

void Pendulum::setAngleOne(float angle)
{
    angleOne = angle;
}

void Pendulum::setAngleTwo(float angle)
{
    angleTwo = angle;
}

float Pendulum::getLengthOne()
{
    return lengthOne;
}

float Pendulum::getLengthTwo()
{
    return lengthTwo;
}

float Pendulum::getMassOne()
{
    return massOne;
}

float Pendulum::getMassTwo()
{
    return massTwo;
}

float Pendulum::getAngleOne()
{
    return angleOne;
}

float Pendulum::getAngleTwo()
{
    return angleTwo;
}

void Pendulum::update(float deltaTime)
{
    // Calculate the angular acceleration for both pendulums
    float num1 = -gravity * (2 * massOne + massTwo) * sin(angleOne);
    float num2 = -massTwo * gravity * sin(angleOne - 2 * angleTwo);
    float num3 = -2 * sin(angleOne - angleTwo) * massTwo;
    float num4 = angularVelocityTwo * angularVelocityTwo * lengthTwo +
                 angularVelocityOne * angularVelocityOne * lengthOne * cos(angleOne - angleTwo);
    float den = lengthOne * (2 * massOne + massTwo - massTwo * cos(2 * angleOne - 2 * angleTwo));
    angularAccelerationOne = (num1 + num2 + num3 * num4) / den;

    num1 = 2 * sin(angleOne - angleTwo);
    num2 = angularVelocityOne * angularVelocityOne * lengthOne * (massOne + massTwo);
    num3 = gravity * (massOne + massTwo) * cos(angleOne);
    num4 = angularVelocityTwo * angularVelocityTwo * lengthTwo * massTwo * cos(angleOne - angleTwo);
    den = lengthTwo * (2 * massOne + massTwo - massTwo * cos(2 * angleOne - 2 * angleTwo));
    angularAccelerationTwo = (num1 * (num2 + num3 + num4)) / den;

    // Update the angular velocities
    angularVelocityOne += angularAccelerationOne * deltaTime;
    angularVelocityTwo += angularAccelerationTwo * deltaTime;

    // Update the angles
    angleOne += angularVelocityOne * deltaTime;
    angleTwo += angularVelocityTwo * deltaTime;

    // Update the positions
    positionOne = std::make_pair(lengthOne * sin(angleOne) + origin.first, -lengthOne * cos(angleOne) + origin.second);
    positionTwo = std::make_pair(lengthOne * sin(angleOne) + lengthTwo * sin(angleTwo) + origin.first,
                                 -lengthOne * cos(angleOne) - lengthTwo * cos(angleTwo) + origin.second);
}

void Pendulum::draw(sf::RenderWindow &window)
{
    sf::Vertex lineOne[] = {sf::Vertex(sf::Vector2f(origin.first, origin.second)),
                            sf::Vertex(sf::Vector2f(positionOne.first, positionOne.second))};
    sf::Vertex lineTwo[] = {sf::Vertex(sf::Vector2f(positionOne.first, positionOne.second)),
                            sf::Vertex(sf::Vector2f(positionTwo.first, positionTwo.second))};
    lineOne[0].color = sf::Color::Black;
    lineOne[1].color = sf::Color::Black;
    lineTwo[0].color = sf::Color::Black;
    lineTwo[1].color = sf::Color::Black;

    sf::CircleShape pendulumOne(massOne);
    pendulumOne.setFillColor(sf::Color::Red);
    pendulumOne.setOrigin(massOne, massOne);
    pendulumOne.setPosition(positionOne.first, positionOne.second);

    sf::CircleShape pendulumTwo(massTwo);
    pendulumTwo.setFillColor(sf::Color::Blue);
    pendulumTwo.setOrigin(massTwo, massTwo);
    pendulumTwo.setPosition(positionTwo.first, positionTwo.second);

    window.draw(lineOne, 2, sf::Lines);
    window.draw(lineTwo, 2, sf::Lines);
    window.draw(pendulumOne);
    window.draw(pendulumTwo);
}

void Pendulum::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::R)
        {
            reset();
        }
    }
}

void Pendulum::reset()
{
    angleOne = M_PI / 4.0f;
    angleTwo = M_PI / 8.0f;
    angularVelocityOne = 0.0f;
    angularVelocityTwo = 0.0f;
    positionOne = std::make_pair(lengthOne * sin(angleOne) + origin.first, -lengthOne * cos(angleOne) + origin.second);
    positionTwo = std::make_pair(lengthOne * sin(angleOne) + lengthTwo * sin(angleTwo),
                                 -lengthOne * cos(angleOne) - lengthTwo * cos(angleTwo));
}