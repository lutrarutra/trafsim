#pragma once

#include <unordered_map>

#include "trafsim/Road.hpp"
#include "trafsim/DrawableEntity.hpp"

namespace TrafSim
{

class RoadSystem
{
public:
    RoadSystem(std::vector<std::shared_ptr<Road>> &roads) { m_roads = std::move(roads); };
    const std::shared_ptr<RoadNode> closestNode(const sf::Vector2f loc) const;
    //virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    std::vector<std::shared_ptr<Road>> m_roads;
};

} // namespace TrafSim
