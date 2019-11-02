#include "util/VectorMath.hpp"

namespace TrafSim
{

float VectorMath::Size(const sf::Vector2f &v)
{
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

float VectorMath::Distance(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

float VectorMath::Angle(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return (a.x * b.x + a.y * b.y) / (Size(a) * Size(b));
}

sf::Vector2f VectorMath::Lerp(const sf::Vector2f &a, const sf::Vector2f &b, float t)
{
    return a + (b - a) * t;
}

sf::Vector2f VectorMath::Normalize(const sf::Vector2f &v)
{
    return v / Size(v);
}

sf::Vector2f VectorMath::Rotate(const sf::Vector2f &v, float angle)
{
    return sf::Vector2f(v.x * cos(angle) - v.y * sin(angle), v.x * sin(angle) + v.y * cos(angle));
}

std::pair<bool, sf::Vector2f> VectorMath::IntersectionPoint(const sf::Vector2f &v1, const sf::Vector2f &v2, const sf::Vector2f &v3, const sf::Vector2f &v4)
{
    float num = (v1.x - v3.x) * (v3.y - v4.y) - (v1.y - v3.y) * (v3.x - v4.x);
    float den = (v1.x - v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x - v4.x);
    if (den == 0)
        return {false, sf::Vector2f()};

    float t = num / den;
    float x = v1.x + t * (v2.x - v1.x);
    float y = v1.y + t * (v2.y - v1.y);
    return {true, {x, y}};
}

} // namespace TrafSim
