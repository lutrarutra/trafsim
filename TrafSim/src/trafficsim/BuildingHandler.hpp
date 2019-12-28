#pragma once

#include <SFML/Graphics.hpp>

#include "BuildingTile.hpp"
#include "Car.hpp"

namespace ts
{

class BuildingHandler
{

public:
    BuildingHandler(const BuildingTile *building_tile, const Tile *tile, unsigned int handler_id);

    // Returns true if car is leaving
    bool update(const sf::Time &game_time);
    void initDay();

    const BuildingTile *getBuildingTile() const { return building_tile_; }
    const Tile *getClosestRoad() const { return closest_road_; }

    void setClosestRoad(const Tile *closest_road) { closest_road_ = closest_road; }
    unsigned int getId() const { return id_; }

private:
    void dispatchCar();

private:
    const BuildingTile *building_tile_;
    const Tile *closest_road_;
    const unsigned id_;
    // Stores the time when car leaves this building
    std::list<unsigned int> leaving_times_;
    unsigned int capacity_ ;
};

} // namespace ts