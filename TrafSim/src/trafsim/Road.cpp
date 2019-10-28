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

} // namespace TrafSim