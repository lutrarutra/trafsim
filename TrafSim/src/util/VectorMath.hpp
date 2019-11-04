#pragma once


#include <math.h>

#include <SFML/System/Vector2.hpp>

namespace TrafSim
{
class VectorMath
{
public:
    static float Size(const sf::Vector2f &v);

    static float Distance(const sf::Vector2f &a, const sf::Vector2f &b);

    static float Angle(const sf::Vector2f &a, const sf::Vector2f &b);

    static sf::Vector2f Lerp(const sf::Vector2f &a, const sf::Vector2f &b, float t);

    static sf::Vector2f Normalize(const sf::Vector2f &v);

    static sf::Vector2f Rotate(const sf::Vector2f &v, float angle);

    static float IntersectionPoint(const sf::Vector2f &v1, const sf::Vector2f &v2, const sf::Vector2f &v3, const sf::Vector2f &v4);
};

} // namespace TrafSim
