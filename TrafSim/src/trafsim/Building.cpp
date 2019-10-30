#include "Building.hpp"
#include "util/Timer.hpp"

namespace TrafSim
{

void Building::updateVisible(const Window &window)
{
    m_visible_vertices.clear();
    if(window.getZoom() > 2)
        return;
    const int x = window.getWidth();
    const int y = window.getHeight();
    for (unsigned int i = 0; i < m_vertices.size(); ++i)
    {
        if (m_type == sf::Lines)
        {
            if (window.isVisible(m_vertices[i].position, 1.1f))
            {
                m_visible_vertices.push_back(m_vertices[i]);
                m_visible_vertices.push_back(m_vertices[i + 1]);
            }
            ++i;
        }
        else
        {
            if (window.isVisible(m_vertices[i].position, 1.1f))
            {
                m_visible_vertices.push_back(m_vertices[i]);
            }
        }
    }
}

} // namespace TrafSim