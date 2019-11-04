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

    void createIntersection(const std::shared_ptr<Road>& another, const sf::Vector2f& pos, std::shared_ptr<Node> *intersection_nodes);

    std::pair<sf::Vector2f, sf::Vector2f> getEndPoints() const { return {m_begin->getPos(), m_end->getPos()}; }
    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> getLaneBeginNodes() const { return {m_brNode, m_blNode}; }
    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> getLaneEndNodes() const { return {m_erNode, m_elNode}; }
    const sf::Vector2f& getDir() const { return m_dir; }
    bool isHorizontal() const;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    void init();

    std::shared_ptr<Node> m_brNode, m_blNode, m_erNode, m_elNode;

    std::vector<sf::Vertex> m_vertices;
    std::shared_ptr<Node> m_begin, m_end;

    sf::Vector2f m_dir;

    float m_lanewidth;
};
} // namespace TrafSim
