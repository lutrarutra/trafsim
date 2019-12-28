#include "BuildingTile.hpp"

#include <iostream>

namespace ts
{

BuildingTile::BuildingTile(const Tile &tile)
    : Tile(tile.getPos(), tile.getSize(), tile.getTileIndex()), dir_(1, 0)
{
    rect_.setFillColor(sf::Color::White);
    rect_.setOutlineThickness(0.f);
}

void BuildingTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect_, states);
}

} // namespace ts