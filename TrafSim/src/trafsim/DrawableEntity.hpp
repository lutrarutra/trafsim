#pragma once

#include "trafsim/MapEntity.hpp"

namespace TrafSim
{
class DrawableEntity : public MapEntity, public sf::Drawable
{
public:
    //Takes ownership of vertices
    DrawableEntity() : m_type(sf::LineStrip){};
    DrawableEntity(std::vector<sf::Vertex> &vertices, const sf::PrimitiveType type, bool visible);
    virtual void draw(Window &window) const;
    virtual void showVisible(const Window &window);
    virtual void zoomVertices(const Window &window) = 0;
    virtual unsigned int getVertexCount() const { return m_vertices.size(); };

private:
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    //Building will have it's corners specified with osmium::Nodes
    std::vector<sf::Vertex> m_vertices;
    std::vector<sf::Vertex> m_visible_vertices;
    const sf::PrimitiveType m_type;
};
} // namespace TrafSim
