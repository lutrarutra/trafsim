#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

namespace TrafSim
{

class Node : public sf::Drawable
{
public:
    Node(const sf::Vector2f &pos);

    void connect(std::shared_ptr<Node> &another);

    const sf::Vector2f &getPos() const { return m_pos; }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    const sf::Vector2f m_pos;
    std::vector<std::shared_ptr<Node>> m_neighbors;
    sf::CircleShape c;
};

} // namespace TrafSim
