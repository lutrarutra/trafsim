#pragma once

#include <math.h> // cos and other math stuff

#include <SFML/System/Vector2.hpp>

namespace ts
{

// static class for vector math
class VectorMath
{
public:
    static float Size(const sf::Vector2f &v);

    static float Distance(const sf::Vector2f &a, const sf::Vector2f &b);

    //Returns angle in Radians
    static float Angle(const sf::Vector2f &a, const sf::Vector2f &b);

    static float Angle(const sf::Vector2f &a);
    // Linear interpolation
    static sf::Vector2f Lerp(const sf::Vector2f &a, const sf::Vector2f &b, float t);

    static sf::Vector2f Normalize(const sf::Vector2f &v);

    static sf::Vector2f Rotate(const sf::Vector2f &v, float angle);

    // returns float t. If 0 <= t <= 1 there is intersection between two lines specified with points v1, v2 and v3,v4
    static float IntersectionPoint(const sf::Vector2f &v1, const sf::Vector2f &v2, const sf::Vector2f &v3, const sf::Vector2f &v4);
};
} // namespace ts
