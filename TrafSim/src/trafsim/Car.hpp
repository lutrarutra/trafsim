#pragma once

#include <SFML/Graphics.hpp>

#include "trafsim/Node.hpp"
#include "util/Random.hpp"

namespace TrafSim
{

class Car : public sf::Drawable
{
public:
    Car(const std::shared_ptr<Node> &pos, const std::shared_ptr<Node> &target, const sf::Vector2f &size);

    void update(float delta_time);
    void findRoute();
    bool finishedRoute() const { return m_finishedRoute; }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::RectangleShape m_rect;
    // p node as previous node t node as target node, n node as next node
    // from p node to t node via n node
    std::shared_ptr<Node> m_pNode, m_tNode, m_nNode;
    sf::Vector2f size;
    sf::Vector2f m_pos;
    //Velocity and acceleration
    float m_v, m_a;

    std::vector<unsigned int> m_route;

    bool m_finishedRoute = false;
};

}; // namespace TrafSim