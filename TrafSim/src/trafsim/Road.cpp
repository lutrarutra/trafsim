#include "Road.hpp"

namespace TrafSim
{
unique_map Road::s_RoadNodes = std::make_unique<std::unordered_map<unsigned long long, sf::Vector2f>>();

Road::Road(std::unique_ptr<std::vector<unsigned long long>> &node_refs)
{
    m_vertices = std::make_unique<std::vector<sf::Vertex>>();
    for (const auto &ref : *node_refs)
    {
        m_vertices->emplace_back((*Road::s_RoadNodes)[ref]);
    }
}

} // namespace TrafSim