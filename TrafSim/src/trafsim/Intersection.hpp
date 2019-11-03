#pragma once

#include "trafsim/Road.hpp"

namespace TrafSim
{
class Intersection : public sf::Drawable
{
public:
    Intersection(std::shared_ptr<Road> &road1, std::shared_ptr<Road> &road2, const sf::Vector2f& pos);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    const sf::Vector2f m_pos;

    std::pair<std::shared_ptr<Road>, std::shared_ptr<Road>> m_roads;
    std::shared_ptr<Node> m_intersectionNodes[4];
};
} // namespace TrafSim
