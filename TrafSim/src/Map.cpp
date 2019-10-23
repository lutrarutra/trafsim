#include "Map.hpp"

namespace TrafSim
{

Map::Map()
{
}

Map::~Map()
{
    for(auto ptr : m_entities)
        delete ptr;
}

void Map::addEntity(MapEntity *entity_ptr)
{
    m_entities.push_back(entity_ptr);
}

void Map::draw(Window& window) const
{
    for(auto &entity : m_entities)
    {
        entity->draw(window);
    }
}

}; // namespace TrafSim