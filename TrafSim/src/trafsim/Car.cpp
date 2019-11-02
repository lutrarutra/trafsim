#include "Car.hpp"

namespace TrafSim
{

Car::Car(const std::shared_ptr<Node> &pos, const sf::Vector2f &size)
    : m_rect(size), m_pNode(pos), m_tNode(nullptr), m_nNode(nullptr), m_v(0, 0), m_a(0, 0)
{
    
}

void Car::update(float delta_time)
{
    
}

void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_rect);
}


}; // namespace TrafSim