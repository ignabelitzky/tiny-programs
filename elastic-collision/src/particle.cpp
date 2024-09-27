#include "../include/particle.hpp"
#include "../include/utils.hpp"
#include "../include/params.hpp"
#include <cmath>
#include <iostream>

Particle::Particle()
{
    m_position = std::make_pair(0.0f, 0.0f);
    m_velocity = std::make_pair(0.0f, 0.0f);
    m_acceleration = std::make_pair(0.0f, 0.0f);
    m_mass = utils::random(1.0f, 6.0f);
    m_radius = sqrt(m_mass) * 20.0f;
    m_shape.setRadius(m_radius);
    m_shape.setOrigin(m_radius, m_radius);
    m_color = utils::randomColor();
    m_shape.setFillColor(m_color);
    m_shape.setOutlineThickness(1.0f);
}

Particle::~Particle()
{
}

void Particle::setPosition(float x, float y)
{
    m_position = std::make_pair(x, y);
}

void Particle::setVelocity(float vx, float vy)
{
    m_velocity = std::make_pair(vx, vy);
}

void Particle::setAcceleration(float ax, float ay)
{
    m_acceleration = std::make_pair(ax, ay);
}

void Particle::setMass(float mass)
{
    m_mass = mass;
}

void Particle::setRadius(float radius)
{
    m_radius = radius;
}

void Particle::setColor(sf::Color color)
{
    m_color = color;
}

std::pair<float, float> Particle::getPosition()
{
    return m_position;
}

std::pair<float, float> Particle::getVelocity()
{
    return m_velocity;
}

std::pair<float, float> Particle::getAcceleration()
{
    return m_acceleration;
}

float Particle::getMass()
{
    return m_mass;
}

float Particle::getRadius()
{
    return m_radius;
}

sf::Color Particle::getColor()
{
    return m_color;
}

void Particle::update()
{
    m_velocity.first += m_acceleration.first;
    m_velocity.second += m_acceleration.second;
    m_position.first += m_velocity.first;
    m_position.second += m_velocity.second;
}

void Particle::edges()
{
    if (m_position.first > params::WIDTH)
    {
        m_position.first = params::WIDTH;
        m_velocity.first *= -1;
    }
    else if (m_position.first < m_radius * 2)
    {
        m_position.first = m_radius * 2;
        m_velocity.first *= -1;
    }

    if (m_position.second > params::HEIGHT)
    {
        m_position.second = params::HEIGHT;
        m_velocity.second *= -1;
    }
    else if (m_position.second < m_radius * 2)
    {
        m_position.second = m_radius * 2;
        m_velocity.second *= -1;
    }
}

void Particle::collide(Particle *other)
{
    std::pair<float, float> impactVector = std::make_pair(other->getPosition().first - m_position.first, other->getPosition().second - m_position.second);
    float d = sqrt(pow(impactVector.first, 2) + pow(impactVector.second, 2));
    if (d < m_radius + other->getRadius())
    {
        float overlap = d - (m_radius + other->getRadius());
        std::pair<float, float> dir = std::make_pair(impactVector.first, impactVector.second);
        dir = utils::setMagnitude(dir, overlap * 0.5f);
        m_position.first += dir.first;
        m_position.second += dir.second;
        other->setPosition(other->getPosition().first - dir.first, other->getPosition().second - dir.second);

        float mSum = m_mass + other->getMass();
        
        // first particle
        std::pair<float, float> impact  = std::make_pair(other->getPosition().first - m_position.first, other->getPosition().second - m_position.second);
        std::pair<float, float> vDiff = std::make_pair(other->getVelocity().first - m_velocity.first, other->getVelocity().second - m_velocity.second);
        float numA = 2 * other->getMass() * (vDiff.first * impact.first + vDiff.second * impact.second);
        float denA = mSum * pow(d, 2);
        float a = numA / denA;
        m_velocity.first += a * impact.first;
        m_velocity.second += a * impact.second;

        // second particle
        std::pair<float, float> impact2 = std::make_pair(m_position.first - other->getPosition().first, m_position.second - other->getPosition().second);
        std::pair<float, float> vDiff2 = std::make_pair(m_velocity.first - other->getVelocity().first, m_velocity.second - other->getVelocity().second);
        float numB = 2 * m_mass * (vDiff2.first * impact2.first + vDiff2.second * impact2.second);
        float denB = mSum * pow(d, 2);
        float b = numB / denB;
        other->setVelocity(other->getVelocity().first + b * impact2.first, other->getVelocity().second + b * impact2.second);
    }
}

void Particle::draw(sf::RenderWindow &window)
{
    m_shape.setPosition(m_position.first - m_radius, m_position.second - m_radius);
    window.draw(m_shape);
}