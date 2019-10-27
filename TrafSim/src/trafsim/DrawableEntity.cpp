#include "DrawableEntity.hpp"

namespace TrafSim
{

DrawableEntity::DrawableEntity(std::vector<sf::Vertex> &vertices, const sf::PrimitiveType type) : m_type(type)
{
    m_vertices = std::move(vertices);
}

void DrawableEntity::draw(Window &window) const
{
    window.draw(*this);
}

void DrawableEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //PerformanceTimer p;
    //Now it's faster to draw std::vector<sf::Vertex> instread of sf::VertexBuffer
    target.draw(&m_vertices[0], m_vertices.size(), m_type, states);
}

} // namespace TrafSim
