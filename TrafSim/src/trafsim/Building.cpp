#include "Building.hpp"
#include "util/Timer.hpp"

namespace TrafSim
{

float distance(const sf::Vector2i &a, const sf::Vector2i &b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

void Building::zoomVertices(const Window &window)
{
    if(window.getZoom() > 2)
        m_visible_vertices.clear();
}

} // namespace TrafSim