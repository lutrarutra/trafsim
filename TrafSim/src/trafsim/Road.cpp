#include "trafsim/Road.hpp"

namespace TrafSim
{

Road::Road(const std::shared_ptr<Node> &begin, const std::shared_ptr<Node> &end, float lane_width, int lanecount)
    : m_begin(begin), m_end(end), m_lanewidth(lane_width), m_lanecount(lanecount)
{
    m_dir = end->getPos() - begin->getPos();
    m_dir = Normalize(m_dir);

    //Permendicular direction to m_dir
    sf::Vector2f pdir = Rotate(m_dir, M_PI / 2);

    //Begin right, begin left, end right, end left nodes
    m_vertices.emplace_back(begin->getPos() + pdir * m_lanewidth);
    auto brNode = std::make_shared<Node>(m_begin->getPos() + pdir * m_lanewidth * 0.5f);

    m_vertices.emplace_back(begin->getPos() - pdir * m_lanewidth);
    auto blNode = std::make_shared<Node>(m_begin->getPos() - pdir * m_lanewidth * 0.5f);

    m_vertices.emplace_back(end->getPos() + pdir * m_lanewidth);
    auto erNode = std::make_shared<Node>(m_end->getPos() + pdir * m_lanewidth * 0.5f);

    m_vertices.emplace_back(end->getPos() - pdir * m_lanewidth);
    auto elNode = std::make_shared<Node>(m_end->getPos() - pdir * m_lanewidth * 0.5f);

    brNode->connect(erNode);
    blNode->connect(elNode);

    m_laneNodes.push_back(brNode);
    m_laneNodes.push_back(blNode);
    m_laneNodes.push_back(erNode);
    m_laneNodes.push_back(elNode);
}

void Road::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(&m_vertices[0], m_vertices.size(), sf::TriangleStrip);
    for (const auto &node : m_laneNodes)
    {
        target.draw(*node);
    }
}

} // namespace TrafSim
