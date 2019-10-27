#pragma once

#include <unordered_map>

#include "trafsim/RoadNode.hpp"
#include "trafsim/DrawableEntity.hpp"

namespace TrafSim
{

class RoadSystem : public DrawableEntity
{
public:
    RoadSystem(std::vector<std::shared_ptr<RoadNode>> &nodes, std::vector<sf::Vertex> &vertices) : DrawableEntity(vertices, sf::Lines){ m_nodes = std::move(nodes);};
    const std::shared_ptr<RoadNode> closestNode(const sf::Vector2f loc) const;

private:
    std::vector<std::shared_ptr<RoadNode>> m_nodes;
};

} // namespace TrafSim
