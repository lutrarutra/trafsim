#pragma once

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "util/VectorMath.hpp"
#include "trafsim/Node.hpp"

namespace TrafSim
{
class Road : public sf::Drawable
{
public:
    Road(const std::shared_ptr<Node> &begin, const std::shared_ptr<Node> &end, float lane_width);
    Road(const Road &prev_road, const std::shared_ptr<Node> &end);

    void createIntersection(std::shared_ptr<Road> another, sf::Vector2f pos);

    std::pair<sf::Vector2f, sf::Vector2f> getEndPoints() const { return {m_begin->getPos(), m_end->getPos()}; }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    void init(float lane_width);

    std::shared_ptr<Node> m_brNode, m_blNode, m_erNode, m_elNode;
    
    std::vector<std::shared_ptr<Node>> m_intersectionNodes;
    std::vector<sf::Vertex> m_vertices;
    std::shared_ptr<Node> m_begin, m_end;

    sf::Vector2f m_dir;

    float m_lanewidth;
};
} // namespace TrafSim
