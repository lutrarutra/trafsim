#pragma once

#include <SFML/Graphics.hpp>

#include "util/VectorUtil.hpp"

namespace TrafSim
{
class Road : public sf::Drawable
{
public:
    Road(const std::vector<sf::Vector2f> &points, float lane_width, int lanecount = 2);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    std::vector<sf::Vector2f> m_points;
    std::vector<sf::Vertex> m_vertices;
    float m_lanewidth;
    int m_lanecount;
};
} // namespace TrafSim
