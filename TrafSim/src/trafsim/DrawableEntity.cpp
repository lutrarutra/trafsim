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

void DrawableEntity::showVisible(const Window &window)
{
    m_visible_vertices.clear();
    const int x = window.getWidth();
    const int y = window.getHeight();
    for (unsigned int i = 0; i < m_vertices.size(); i)
    {
        // std::cout << window.convert(m_vertices[i].position).x << " " << window.convert(m_vertices[i].position).y << "\n";
        sf::Vector2i convertedPoint = window.convert(m_vertices[i].position);
        if (m_type == sf::Lines)
        {
            if (convertedPoint.x > 0 && convertedPoint.x < x && convertedPoint.y > 0 && convertedPoint.y < y)
            {
                m_visible_vertices.push_back(m_vertices[i]);
                m_visible_vertices.push_back(m_vertices[i+1]);
            }
            i += 2;
        }
        else
        {
            if (convertedPoint.x > 0 && convertedPoint.x < x && convertedPoint.y > 0 && convertedPoint.y < y)
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
