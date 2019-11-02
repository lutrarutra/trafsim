#pragma once

#include <SFML/Graphics.hpp>

#include "trafsim/Node.hpp"

namespace TrafSim
{

class Car : public sf::Drawable
{
public:
    Car(const std::shared_ptr<Node> &pos, const sf::Vector2f &size);
    void update(float delta_time);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::RectangleShape m_rect;
    // p node as previous node t node as target node, n node as next node
    // from p node to t node via n node
    std::shared_ptr<Node> m_pNode, m_tNode, m_nNode;
    const sf::Vector2f size;
    //Velocity and acceleration
    sf::Vector2f m_v, m_a;
};

};