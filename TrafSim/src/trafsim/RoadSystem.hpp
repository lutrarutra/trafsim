#pragma once

#include <unordered_map>

#include "trafsim/RoadNode.hpp"
#include "trafsim/DrawableEntity.hpp"

namespace TrafSim
{

class RoadSystem : public DrawableEntity
{
public:
    RoadSystem(std::vector<std::shared_ptr<RoadNode>> &nodes, std::unique_ptr<std::vector<Road>> &roads);
    const std::shared_ptr<RoadNode> closestNode(const sf::Vector2f loc) const;
    virtual void draw(Window &window) const;

private:
    std::vector<std::shared_ptr<RoadNode>> m_nodes;
    std::unique_ptr<std::vector<Road>> m_roads;
};

} // namespace TrafSim