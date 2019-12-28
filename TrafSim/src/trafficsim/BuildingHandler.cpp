#include "BuildingHandler.hpp"

#include <algorithm>

#include "Rando.hpp"

namespace ts
{

BuildingHandler::BuildingHandler(const BuildingTile *building_tile, const Tile *tile, unsigned int handler_id)
    : building_tile_(building_tile), closest_road_(tile), id_(handler_id)
{
    Rando r(100, 25);
    capacity_ = r.roll();
    initDay();
}

void BuildingHandler::initDay()
{
    float leaving_mean;
    switch (building_tile_->getType())
    {
    case HomeBuildingType:
    {
        Rando r(28800, 3600);
        leaving_mean = r.roll();
        break;
    }
    case OfficeBuildingType:
    {
        Rando r(57600, 3600);
        leaving_mean = r.roll();
        break;
    }
    default:
        break;
    }
    std::vector<unsigned int> times;
    times.reserve(capacity_);
    Rando r(leaving_mean, 60 * 30);
    for (unsigned int i = 0; i < capacity_; ++i)
        times.emplace_back(r.roll());

    std::sort(times.begin(), times.end(), [](const auto &t1, const auto &t2) -> bool {
        return t1 < t2;
    });
    for (unsigned int i = 0; i < capacity_; ++i)
        leaving_times_.emplace_back(times[i]);
}

bool BuildingHandler::update(const sf::Time &game_time)
{
    if (leaving_times_.size() > 0 && leaving_times_.front() <= game_time.asSeconds())
    {
        while (leaving_times_.front() && leaving_times_.front() <= game_time.asSeconds())
            leaving_times_.pop_front();
        return true;
    }
    return false;
}

void BuildingHandler::dispatchCar()
{
}

} // namespace ts