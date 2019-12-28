#pragma once

#include <SFML/Graphics.hpp>

#include "BuildingTile.hpp"

namespace ts
{

class HomeBuilding : public BuildingTile
{
public:
    HomeBuilding(const Tile &tile);
    virtual BuildingType getType() const { return BuildingType::HomeBuildingType; }

    static void SetTexture(const sf::Texture *texture);

private:
    const static sf::Texture *Texture;
};
} // namespace ts