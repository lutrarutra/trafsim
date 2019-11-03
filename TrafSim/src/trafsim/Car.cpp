#include "Car.hpp"

namespace TrafSim
{

Car::Car(const std::shared_ptr<Node> &pos, const std::shared_ptr<Node> &target, const sf::Vector2f &size)
    : m_rect(size), m_pNode(pos), m_tNode(target), m_nNode(nullptr), m_pos(pos->getPos()), m_v(0.1f), m_a(0)
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
    if (m_tNode == nullptr)
        return;
    if (VectorMath::Distance(m_pos, m_tNode->getPos()) < 3.f)
        if (m_tNode->getNeighbors().size() > 0)
            m_tNode = m_tNode->getNeighbors()[0];
        else
        {
            m_tNode = nullptr;
            return;
        }

    sf::Vector2f dir = VectorMath::Normalize(m_tNode->getPos() - m_pNode->getPos());
    m_pos += dir * delta_time * m_v;
    m_rect.setPosition(m_pos);
}

void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_rect);
}

}; // namespace TrafSim