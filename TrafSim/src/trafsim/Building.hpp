#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "trafsim/DrawableEntity.hpp"

namespace TrafSim
{

class Building : public DrawableEntity
{
public:
    //Takes ownership of vertices
    Building(std::vector<sf::Vertex> &verticies) : DrawableEntity(verticies, sf::LineStrip){};
private:

};

} // namespace TrafSim