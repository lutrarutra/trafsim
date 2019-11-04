#include "trafsim/Intersection.hpp"

namespace TrafSim
{

Intersection::Intersection(const std::shared_ptr<Road> &road1,const std::shared_ptr<Road> &road2, const sf::Vector2f &pos)
    : m_pos(pos), m_roads({road1, road2})
{
    road1->createIntersection(road2, m_pos, m_intersectionNodes);
    road2->createIntersection(road1, m_pos, m_intersectionNodes);

    // intersection nodes top left, torright, bot right, bot left.
    std::shared_ptr<Node> &tlNode = m_intersectionNodes[0];
    std::shared_ptr<Node> &trNode = m_intersectionNodes[1];
    std::shared_ptr<Node> &brNode = m_intersectionNodes[2];
    std::shared_ptr<Node> &blNode = m_intersectionNodes[3];


    tlNode->connect(blNode);
    blNode->connect(brNode);
    brNode->connect(trNode);
    trNode->connect(tlNode);

}

void Intersection::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int i = 0; i < 4; ++i)
        target.draw(*(m_intersectionNodes[i]));
}

} // namespace TrafSim
