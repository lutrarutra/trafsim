#pragma once

#include "MapEntity.hpp"

namespace TrafSim
{
class Road : public MapEntity, public sf::Drawable
{
public:
    Road();
    virtual void draw(Window& window) const;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
};
} // namespace TrafSim
