#include "trafsim/Road.hpp"

namespace TrafSim
{

Road::Road(const std::vector<sf::Vector2f> &points, float lane_width, int lanecount)
    : m_points(points), m_lanewidth(lane_width), m_lanecount(lanecount)
{
    for (unsigned int i = 0; i < m_points.size(); ++i)
    {
        sf::Vector2f dir(0, 0);
        if (i < m_points.size() - 1)
        {
            dir += m_points[i + 1] - m_points[i];
        }
        if (i > 0)
        {
            dir += m_points[i] - m_points[i - 1];
        }
        dir = Normalize(dir);
        dir = Rotate(dir, M_PI / 2);
        m_vertices.emplace_back(m_points[i] + dir * m_lanewidth);
        m_vertices.emplace_back(m_points[i] - dir * m_lanewidth);
        // perpendicular
        auto rNode = std::make_shared<Node>(m_points[i] + dir * m_lanewidth * 0.5f);
        if (m_nodes.size() > 1)
            m_nodes[m_nodes.size() - 2]->connect(rNode);
        m_nodes.push_back(rNode);
        auto lNode = std::make_shared<Node>(m_points[i] - dir * m_lanewidth * 0.5f);
        if (m_nodes.size() > 1)
            m_nodes[m_nodes.size() - 2]->connect(lNode);
        m_nodes.push_back(lNode);
    }
}

void Road::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(&m_vertices[0], m_vertices.size(), sf::TriangleStrip);
    for(const auto& node : m_nodes)
    {
        target.draw(*node);
    }
}

} // namespace TrafSim
