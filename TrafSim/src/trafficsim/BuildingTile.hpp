#pragma once

#include <array>
#include <climits> // UINT_MAX

#include <SFML/Graphics.hpp>

#include "Tile.hpp"
#include "TrafficLight.hpp"

namespace ts
{

enum BuildingType
{
    HomeBuildingType = 0,
    OfficeBuildingType,

    // Keep last
    BuildingTypeCount
};

class BuildingTile : public Tile
{
public:
    BuildingTile(const Tile &tile);

    virtual TileCategory getCategory() const { return TileCategory::BuildingCategory; };
    virtual BuildingType getType() const = 0;

    // Direction of the building
    // Up: { 0, 1 }, Right { 1, 0 }, Down { 0, -1 }, Left { -1, 0 }
    const sf::Vector2f &getDir() const { return dir_; }
    unsigned int getId() const { return id_; }
    void setId(unsigned int id) { id_ = id; }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
    // Up: { 0, 1 }, Right { 1, 0 }, Down { 0, -1 }, Left { -1, 0 }
    sf::Vector2f dir_;
    unsigned int id_;
};
} // namespace ts