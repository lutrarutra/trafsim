#pragma once 

#include <math.h>

#include <SFML/System/Vector2.hpp>

namespace TrafSim
{

static float Size(const sf::Vector2f &v)
{
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

static float Distance(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}
    
static float Angle(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return (a.x * b.x + a.y * b.y) / (Size(a) * Size(b));
}

static sf::Vector2f Lerp(const sf::Vector2f &a, const sf::Vector2f &b, float t)
{
    return a + (b - a) * t;
}

static sf::Vector2f Normalize(const sf::Vector2f &v)
{
    return v / Size(v);
}

static sf::Vector2f Rotate(const sf::Vector2f &v, float angle)
{
    return sf::Vector2f(v.x * cos(angle) - v.y * sin(angle), v.x * sin(angle) + v.y * cos(angle));
}

} // namespace TrafSim
