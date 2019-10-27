#pragma once

#include <unordered_map>

#include "DrawableEntity.hpp"

namespace TrafSim
{

class Road : public DrawableEntity
{
public:
    //Takes ownership of vertices
    Road(std::vector<sf::Vertex> &verticies) : DrawableEntity(verticies, sf::LineStrip){};
    
};
} // namespace TrafSim
