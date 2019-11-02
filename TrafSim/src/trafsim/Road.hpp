#pragma once

#include <SFML/Graphics.hpp>

#include "util/VectorMath.hpp"
#include "trafsim/Node.hpp"

namespace TrafSim
{
class Road : public sf::Drawable
{
public:
    Road(const std::shared_ptr<Node> &begin, const std::shared_ptr<Node> &end, float lane_width, int lanecount = 2);
    Road(const Road &prev_road, const std::shared_ptr<Node> &end);
    const std::vector<std::shared_ptr<Node>> &getLaneNodes() const { return m_laneNodes; }
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    std::pair<sf::Vector2f, sf::Vector2f> getEndPoints() const { return {m_begin->getPos(), m_end->getPos()}; }

private:
    void init(const std::shared_ptr<Node> &begin, const std::shared_ptr<Node> &end, float lane_width, int lanecount);

    std::vector<sf::Vertex> m_vertices;
    std::vector<std::shared_ptr<Node>> m_laneNodes;
    std::shared_ptr<Node> m_begin, m_end;

    sf::Vector2f m_dir;

    float m_lanewidth;
    int m_lanecount;
};
} // namespace TrafSim
