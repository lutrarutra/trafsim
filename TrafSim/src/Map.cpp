#include "Map.hpp"

namespace TrafSim
{

Map::Map()
    : zoom_(0)
{
}

void Map::add_entity(std::shared_ptr<MapEntity> entity_ptr)
{
    entities_.push_back(entity_ptr);
}

void Map::zoom(int z)
{
    zoom_ += z;
    for (auto entity : entities_)
    {
        entity->scale(z * 0.1f);
    }
}

void Map::draw(Window &window) const
{
    for(auto entity : entities_)
    {
        entity->draw(window);
    }
}

}; // namespace TrafSim