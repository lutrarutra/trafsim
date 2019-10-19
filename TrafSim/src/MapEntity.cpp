#include "MapEntity.hpp"

namespace TrafSim
{

MapEntity::MapEntity(float lon, float lat)
    : loc_(lon, lat)
{
}

void MapEntity::set_loc(float lon, float lat)
{
    loc_.set_lon(lon);
    loc_.set_lat(lat);
}

}; // namespace TrafSim