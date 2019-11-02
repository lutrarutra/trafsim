#include "Car.hpp"

namespace TrafSim
{

Car::Car()
{
    
}

void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_rect);
}


}; // namespace TrafSim