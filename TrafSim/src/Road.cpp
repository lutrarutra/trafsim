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
    //target.draw(?, states);
}

} // namespace TrafSim