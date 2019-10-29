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

void Road::zoomVertices(const Window &window)
{
    // if (window.isVisible(m_vertices[0].position))
    // {
    //     m_visible_vertices.clear();
    //     m_visible_vertices.push_back(m_vertices[0]);
    //     for (unsigned int i = 1; i < m_vertices.size() - 1; ++i)
    //     {

    //         const sf::Vector2i v1 = window.convert(m_visible_vertices[m_visible_vertices.size() - 1].position);
    //         const sf::Vector2i v2 = window.convert(m_visible_vertices[i].position);
    //         const sf::Vector2i v3 = window.convert(m_visible_vertices[i + 1].position);

    //         const float d1 = sqrt(pow(v3.x - v1.x, 2) + pow(v3.y - v1.y, 2));
    //         const float d2 = sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2)) + sqrt(pow(v3.x - v2.x, 2) + pow(v3.y - v2.y, 2));

    //         if (((d1 * 1.01f) > d2))
    //         {
    //             m_visible_vertices.push_back(m_vertices[i]);
    //         }
    //     }
    //     m_visible_vertices.push_back(m_vertices[m_vertices.size() - 1]);
    // }
}

} // namespace TrafSim