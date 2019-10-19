#include "Map.hpp"

namespace TrafSim
{

Map::Map()
{

};

void Map::zoom(int z)
{
    zoom_ += z;
}

void Map::draw(Window &window) const
{

}

}; // namespace TrafSim