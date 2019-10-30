#include "Road.hpp"

namespace TrafSim
{

Road::Road(const std::vector<std::shared_ptr<RoadNode>> nodes, bool visible) : m_nodes(std::move(nodes))
{
    for (const auto &node : m_nodes)
        m_vertices.emplace_back(node->getLocation());

    if (visible)
        m_visible_vertices = std::vector<sf::Vertex>(m_vertices);
}

void Road::updateVisible(const Window &window)
{
    m_visible_vertices.clear();
    const int x = window.getWidth();
    const int y = window.getHeight();
    for (unsigned int i = 0; i < m_vertices.size(); ++i)
    {
        if (m_type == sf::Lines)
        {
            if (window.isVisible(m_vertices[i].position, 1.5f))
            {
                m_visible_vertices.push_back(m_vertices[i]);
                m_visible_vertices.push_back(m_vertices[i + 1]);
            }
            ++i;
        }
        else
        {
            if (window.isVisible(m_vertices[i].position, 1.5f))
            {
                m_visible_vertices.push_back(m_vertices[i]);
            }
        }
    }
}
} // namespace TrafSim