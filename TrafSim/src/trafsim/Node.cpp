#include "trafsim/Node.hpp"

namespace TrafSim
{

sf::RectangleShape makeArrow(sf::Vector2f pos, sf::Color color)
{
    sf::RectangleShape arr(sf::Vector2f(20.f, 6.f));
    arr.setOrigin(0, 3.f);
    arr.setPosition(pos);
    arr.setFillColor(color);
    return arr;
}

Node::Node(const sf::Vector2f &pos, sf::Color color) : m_pos(pos)
{
    m_arrows.push_back(makeArrow(pos, color));
}

void Node::disconnect(const std::shared_ptr<Node> &node)
{
    for (auto it = m_neighbors.begin(); it != m_neighbors.end(); ++it)
    {
        if (node == *it)
        {
            std::cout << "disconnecteded" << std::endl;
            m_neighbors.erase(it);
            return;
        }
    }
}

void Node::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(const auto& arrow : m_arrows)
        target.draw(arrow);
}

void Node::connect(std::shared_ptr<Node> &another)
{
    m_neighbors.push_back(another);
    m_arrows.push_back(makeArrow(m_pos, sf::Color::Green));
    m_arrows[m_arrows.size()-1].rotate(VectorMath::Angle(another->m_pos - m_pos, {1,0}) * 180 / M_PI);
}

} // namespace TrafSim