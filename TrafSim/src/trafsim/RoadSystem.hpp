#pragma once

#include <unordered_map>

#include "trafsim/RoadNode.hpp"
#include "trafsim/DrawableEntity.hpp"

namespace TrafSim
{

class RoadSystem : public DrawableEntity
{
public:
    RoadSystem(std::unique_ptr<std::vector<RoadNode>> &nodes, std::unique_ptr<std::vector<Road>> &roads);
    virtual void draw(Window &window) const;
private:
    std::unique_ptr<std::vector<sf::Vector2f>> m_roadPoints;
    std::unique_ptr<std::vector<RoadNode>> m_nodes;
    std::unique_ptr<std::vector<Road>> m_roads;
};

} // namespace TrafSim
