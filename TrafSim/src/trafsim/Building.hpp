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
    Building(std::unique_ptr<std::vector<sf::Vertex>> &vertices);

private:

};

} // namespace TrafSim