#include "Map.hpp"

namespace TrafSim
{

Map::Map()
{
}

void Map::createRoads(const std::vector<std::shared_ptr<Node>> &nodes)
{
    for (const auto &node : nodes)
    {
        std::cout << node->getPos().x << " " << node->getPos().y << "\n";
        for (const auto &neighbor : node->getNeighbors())
        {
            std::cout << neighbor->getPos().x << " " << neighbor->getPos().y << "\n";
            m_roads.emplace_back(node, neighbor, 100.f);
        }
    }
}

void Map::draw(Window &window) const
{
    for (const auto &road : m_roads)
        window.draw(road);
}

}; // namespace TrafSim