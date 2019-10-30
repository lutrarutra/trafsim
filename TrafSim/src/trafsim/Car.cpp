#include "Car.hpp"

namespace TrafSim
{

Car::Car(float lon, float lat)
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