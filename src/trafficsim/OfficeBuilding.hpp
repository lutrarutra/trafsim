#pragma once

#include <SFML/Graphics.hpp>

#include "BuildingTile.hpp"

namespace ts
{

class OfficeBuilding : public BuildingTile
{
public:
    OfficeBuilding(const Tile &tile);
    virtual BuildingType getType() const { return BuildingType::OfficeBuildingType; }
    static void SetTexture(const sf::Texture *texture);

private:
    const static sf::Texture *Texture;
};
} // namespace ts