#pragma once

#include <SFML/Graphics.hpp>

#include "trafsim/Node.hpp"

namespace TrafSim
{

class Car : public sf::Drawable
{
public:
    Car();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::RectangleShape m_rect;
    // p node as previous node t node as target node, where the car is going to
    // from p node to t node
    std::shared_ptr<Node> m_pNode, m_tNode;
};

};