#include "DrawableEntity.hpp"

namespace TrafSim
{

DrawableEntity::DrawableEntity(std::vector<sf::Vertex> &vertices, sf::PrimitiveType type) : m_buffer(type, sf::VertexBuffer::Usage::Static)
{
    m_vertices = std::move(vertices);
    m_buffer.create(m_vertices.size());
    m_buffer.update(m_vertices.data());
}

void DrawableEntity::draw(Window &window) const
{
    window.draw(*this);
}

void DrawableEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //PerformanceTimer p;
    //Now it's faster to draw std::vector<sf::Vertex> instread of sf::VertexBuffer
    //target.draw(&(*m_vertices)[0], m_vertices->size(), sf::LineStrip, states);
    target.draw(m_buffer, states);
}

} // namespace TrafSim
