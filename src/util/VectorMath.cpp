#include "VectorMath.hpp"

namespace ts
{

float VectorMath::Size(const sf::Vector2f &v)
{
    return Distance(v, {0, 0});
}

float VectorMath::Distance(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

float VectorMath::Angle(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return acos((a.x * b.x + a.y * b.y) / (Size(a) * Size(b)));
}

float VectorMath::Angle(const sf::Vector2f &a)
{
    return a.x < 0 ? - Angle(a, {1, 0}) : Angle(a, {1,0});
}

sf::Vector2f VectorMath::Normalize(const sf::Vector2f &v)
{
    return v / Size(v);
}

sf::Vector2f VectorMath::Rotate(const sf::Vector2f &v, float angle)
{
    if (angle == M_PI * 0.5f)
        return {-v.y, v.x};
    return sf::Vector2f(v.x * cos(angle) - v.y * sin(angle), v.x * sin(angle) + v.y * cos(angle));
}

sf::Vector2f VectorMath::Lerp(const sf::Vector2f &a, const sf::Vector2f &b, float t)
{
    return a + (b - a) * t;
}

float VectorMath::IntersectionPoint(const sf::Vector2f &v1, const sf::Vector2f &v2, const sf::Vector2f &v3, const sf::Vector2f &v4)
{
    float num = (v1.x - v3.x) * (v3.y - v4.y) - (v1.y - v3.y) * (v3.x - v4.x);
    float den = (v1.x - v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x - v4.x);
    if (den == 0)
        return -1.f;

    return num / den;
}

} // namespace ts
