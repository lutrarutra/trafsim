#include "DrawableEntity.hpp"

namespace TrafSim
{

DrawableEntity::DrawableEntity(std::vector<sf::Vertex> &vertices, const sf::PrimitiveType type, bool visible) : m_type(type)
{
    m_vertices = std::move(vertices);
    if(visible)
        m_visible_vertices = std::vector<sf::Vertex>(m_vertices);
}

void DrawableEntity::draw(Window &window) const
{
    window.draw(*this);
}

void DrawableEntity::showVisible(const Window &window)
{
    m_visible_vertices.clear();
    const int x = window.getWidth();
    const int y = window.getHeight();
    for (unsigned int i = 0; i < m_vertices.size(); i)
    {
        if (m_type == sf::Lines)
        {
            if (window.isVisible(m_vertices[i].position))
            {
                m_visible_vertices.push_back(m_vertices[i]);
                m_visible_vertices.push_back(m_vertices[i + 1]);
            }
            i += 2;
        }
        else
        {
            if (window.isVisible(m_vertices[i].position))
            {
                m_visible_vertices.push_back(m_vertices[i]);
            }
            ++i;
        }
    }
}

void DrawableEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //PerformanceTimer p;
    //Now it's faster to draw std::vector<sf::Vertex> instread of sf::VertexBuffer
    target.draw(&m_visible_vertices[0], m_visible_vertices.size(), m_type, states);
}

} // namespace TrafSim
