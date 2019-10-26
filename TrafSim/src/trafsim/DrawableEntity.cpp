#include "DrawableEntity.hpp"

namespace TrafSim
{

DrawableEntity::DrawableEntity(std::unique_ptr<std::vector<sf::Vertex>> &vertices) : m_buffer(sf::LineStrip, sf::VertexBuffer::Usage::Static)
{
    m_vertices.swap(vertices);
}

void DrawableEntity::draw(Window &window) const
{
    window.draw(*this);
}

void DrawableEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //PerformanceTimer p;
    //Now it's faster to draw std::vector<sf::Vertex> instread of sf::VertexBuffer
    target.draw(&(*m_vertices)[0], m_vertices->size(), sf::LineStrip, states);
    //target.draw(m_buffer, states);
}

} // namespace TrafSim
