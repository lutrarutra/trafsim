#include "trafsim/Node.hpp"

namespace TrafSim
{

Node::Node(const sf::Vector2f &pos) : m_pos(pos)
{
    c.setRadius(5.f);
    c.setOrigin(5.f, 5.f);
    c.setFillColor(sf::Color::Red);
    c.setPosition(pos);
}

void Node::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(c);
}

void Node::connect(std::shared_ptr<Node> &another)
{
    m_neighbors.push_back(another);
}

} // namespace TrafSim