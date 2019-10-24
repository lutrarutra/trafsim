#include "Road.hpp"

namespace TrafSim
{

Road::Road(std::unique_ptr<std::vector<sf::Vertex>> &vertices) : DrawableEntity(vertices)
{
}


} // namespace TrafSim