#pragma once

#include <unordered_map>

#include "DrawableEntity.hpp"

namespace TrafSim
{
typedef std::unique_ptr<std::unordered_map<unsigned long long, sf::Vector2f>> unique_map;

class Road : public DrawableEntity
{
public:
    //Takes ownership of vertices
    Road(std::unique_ptr<std::vector<unsigned long long>> &node_refs);
    static unique_map s_RoadNodes;
};
} // namespace TrafSim
