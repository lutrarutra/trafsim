#include "Car.hpp"

namespace TrafSim
{

Car::Car(const std::shared_ptr<Node> &pos, const std::shared_ptr<Node> &target, const sf::Vector2f &size)
    : m_rect(size), m_pNode(pos), m_tNode(target), m_nNode(nullptr), m_pos(pos->getPos()), m_v(0, 0), m_a(0, 0)
{
    m_rect.setOrigin(size * 0.5f);
    m_rect.setPosition(m_pos);
    m_rect.setFillColor(sf::Color::Yellow);
}

void Car::findRoute()
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