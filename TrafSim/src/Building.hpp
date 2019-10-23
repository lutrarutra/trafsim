#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "MapEntity.hpp"

namespace TrafSim
{

class Building : public MapEntity, public sf::Drawable
{
public:
    //Makes unique pointer from parameter and stores it
    Building(std::vector<sf::Vertex> *vertices);
    virtual void draw(Window& window) const;
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    //Building will have it's corners specified with osmium::Nodes
    std::unique_ptr<std::vector<sf::Vertex>> m_vertices;
};

} // namespace TrafSim