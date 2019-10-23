#include "Building.hpp"

namespace TrafSim
{

Building::Building(std::vector<sf::Vertex> *node_ptr)
{
    m_vertices.reset(node_ptr);
}

void Building::draw(Window &window) const
{
    window.draw(*this);
}

void Building::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(&(*m_vertices)[0], m_vertices->size(), sf::TriangleFan, states);
}

} // namespace TrafSim