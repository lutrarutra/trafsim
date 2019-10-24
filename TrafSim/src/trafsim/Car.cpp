#include "Car.hpp"

namespace TrafSim
{

Car::Car(float lon, float lat)
    : MapEntity(lon, lat), m_rect(sf::Vector2f(10.0f, 10.0f))
{
    m_rect.setPosition(300, 300);
}

void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_rect, states);
}

void Car::draw(Window &window) const
{
    window.draw(*this);
}

}; // namespace TrafSim