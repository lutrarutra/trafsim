#pragma once

#include "trafsim/MapEntity.hpp"

namespace TrafSim
{
class DrawableEntity : public MapEntity, public sf::Drawable
{
public:
    //Takes ownership of vertices
    DrawableEntity() : m_type(sf::Lines){};
    DrawableEntity(std::vector<sf::Vertex> &vertices, const sf::PrimitiveType type);
    virtual void draw(Window &window) const;
    virtual void showVisible(const Window &window);
private:
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    //Building will have it's corners specified with osmium::Nodes
    std::vector<sf::Vertex> m_vertices;
    std::vector<sf::Vertex> m_visible_vertices;
    const sf::PrimitiveType m_type;
};
} // namespace TrafSim
