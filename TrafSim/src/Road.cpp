#include "Road.hpp"

namespace TrafSim
{

Road::Road()
{
}

void Road::draw(Window &window) const
{
    window.draw(*this);
}

void Road::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // TODO - how to store vertices of the road?
    //target.draw(?, states);
}

} // namespace TrafSim