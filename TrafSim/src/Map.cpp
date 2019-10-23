#include "Map.hpp"

namespace TrafSim
{

Map::Map()
{
}

void Map::addEntity(std::shared_ptr<MapEntity> entity_ptr)
{
    m_entities.push_back(entity_ptr);
}

void Map::draw(Window& window) const
{
    for(auto entity : m_entities)
    {
        entity->draw(window);
    }
}

}; // namespace TrafSim