#pragma once

#include <unordered_map>

#include "DrawableEntity.hpp"

namespace TrafSim
{

class Road : public DrawableEntity
{
public:
    //Takes ownership of vertices
    Road(std::unique_ptr<std::vector<sf::Vertex>> &vertices);
    
};
} // namespace TrafSim
