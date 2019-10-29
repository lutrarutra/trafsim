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
    Building(std::vector<sf::Vertex> &verticies, bool visible = false) : DrawableEntity(verticies, sf::LineStrip, visible){};
    virtual void zoomVertices(const Window &window);
private:

};

} // namespace TrafSim