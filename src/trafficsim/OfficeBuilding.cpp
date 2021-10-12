#include "OfficeBuilding.hpp"

#include <iostream>

namespace ts
{

const sf::Texture *OfficeBuilding::Texture;

OfficeBuilding::OfficeBuilding(const Tile &tile)
    : BuildingTile(tile)
{
    rect_.setTexture(OfficeBuilding::Texture);
}

void OfficeBuilding::SetTexture(const sf::Texture *texture)
{
    OfficeBuilding::Texture = texture;
}

} // namespace ts