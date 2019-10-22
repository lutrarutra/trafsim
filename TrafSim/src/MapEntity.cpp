#include "MapEntity.hpp"

namespace TrafSim
{

MapEntity::MapEntity(float lon, float lat)
    : m_loc(lon, lat)
{
}


void MapEntity::setLoc(float lon, float lat)
{
    m_loc.set_lon(lon);
    m_loc.set_lat(lat);
}

}; // namespace TrafSim