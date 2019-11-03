#include "trafsim/Node.hpp"

namespace TrafSim
{

Node::Node(const sf::Vector2f &pos, sf::Color color)
    : m_pos(pos), c(6.f)
{
    c.setOrigin(3.f, 3.f);
    c.setPosition(m_pos);
    c.setFillColor(color);
}


void Node::disconnect(const std::shared_ptr<Node> &node)
{
    for (auto it = m_neighbors.begin(); it != m_neighbors.end(); ++it)
    {
        if (node == *it)
        {
            m_neighbors.erase(it);
            return;
        }
    }
}

void Node::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(c);
}

void Node::connect(std::shared_ptr<Node> another)
{
    m_neighbors.push_back(another);
}

} // namespace TrafSim