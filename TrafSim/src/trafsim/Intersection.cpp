#include "trafsim/Intersection.hpp"

namespace TrafSim
{

Intersection::Intersection(std::shared_ptr<Road> &road1, std::shared_ptr<Road> &road2, const sf::Vector2f &pos)
    : m_pos(pos), m_roads({road1, road2})
{
    for (int i = 0; i < 4; ++i)
        m_intersectionNodes[i] = nullptr;
    road1->createIntersection(road2, m_pos, m_intersectionNodes);
    road2->createIntersection(road1, m_pos, m_intersectionNodes);
}

void Intersection::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int i = 0; i < 4; ++i)
        target.draw(*(m_intersectionNodes[i]));
}

} // namespace TrafSim
