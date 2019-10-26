#pragma once

#include "trafsim/MapEntity.hpp"

namespace TrafSim
{
class DrawableEntity : public MapEntity, public sf::Drawable
{
public:
    //Takes ownership of vertices
    DrawableEntity(){};
    DrawableEntity(std::unique_ptr<std::vector<sf::Vertex>> &vertices);
    virtual void draw(Window &window) const;
    
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
    //Building will have it's corners specified with osmium::Nodes
    std::unique_ptr<std::vector<sf::Vertex>> m_vertices;
    sf::VertexBuffer m_buffer;
};
} // namespace TrafSim
