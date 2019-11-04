#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "util/VectorMath.hpp"

namespace TrafSim
{

class Node : public sf::Drawable
{
public:
    Node(const sf::Vector2f &pos, sf::Color color = sf::Color::Red);

    void connect(const std::shared_ptr<Node> &another);
    void disconnect(const std::shared_ptr<Node> &node);

    const sf::Vector2f &getPos() const { return m_pos; }
    const std::vector<std::shared_ptr<Node>> &getNeighbors() const { return m_neighbors; }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Vector2f m_pos;
    std::vector<std::shared_ptr<Node>> m_neighbors;
    sf::CircleShape c;
};

} // namespace TrafSim
