#pragma once

#include <SFML/Graphics.hpp>

#include "util/VectorUtil.hpp"
#include "trafsim/Node.hpp"

namespace TrafSim
{
class Road : public sf::Drawable
{
public:
    Road(const std::shared_ptr<Node> &begin, const std::shared_ptr<Node> &end, float lane_width, int lanecount = 2);
    const std::vector<std::shared_ptr<Node>> &getLaneNodes() const { return m_laneNodes; }
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    std::vector<sf::Vector2f> m_points;
    std::vector<sf::Vertex> m_vertices;
    std::vector<std::shared_ptr<Node>> m_laneNodes;
    std::shared_ptr<Node> m_begin, m_end;

    sf::Vector2f m_dir;

    float m_lanewidth;
    int m_lanecount;
};
} // namespace TrafSim
