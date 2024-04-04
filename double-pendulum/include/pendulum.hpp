#ifndef PENDULUM_HPP
#define PENDULUM_HPP

#include "constants.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <utility>

class Pendulum
{
  public:
    Pendulum();
    ~Pendulum();
    void setLengthOne(float length);
    void setLengthTwo(float length);
    void setMassOne(float mass);
    void setMassTwo(float mass);
    void setAngleOne(float angle);
    void setAngleTwo(float angle);
    float getLengthOne();
    float getLengthTwo();
    float getMassOne();
    float getMassTwo();
    float getAngleOne();
    float getAngleTwo();
    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    void handleEvent(const sf::Event &event);
    void reset();

  private:
    std::pair<float, float> origin;
    float lengthOne;
    float lengthTwo;
    float massOne;
    float massTwo;
    float angleOne;
    float angleTwo;
    std::pair<float, float> positionOne;
    std::pair<float, float> positionTwo;
    float gravity;
    float angularVelocityOne;
    float angularVelocityTwo;
    float angularAccelerationOne;
    float angularAccelerationTwo;
};

#endif