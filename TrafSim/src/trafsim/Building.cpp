#include "Building.hpp"
#include "util/Timer.hpp"

namespace TrafSim
{


Building::Building(std::unique_ptr<std::vector<sf::Vertex>> &vertices) : DrawableEntity(vertices)
{
    // m_vertices.swap(vertices);
    // // m_buffer.create(m_vertices->size());
    // // m_buffer.update(m_vertices->data());
}


} // namespace TrafSim