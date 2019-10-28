#include "Map.hpp"

namespace TrafSim
{

Map::Map()
{
}

Map::~Map()
{
    // for(auto ptr : m_entities)
    //     delete ptr;
}

void Map::showVisible(const Window& window)
{
    for(auto& entity : m_entities)
    {
        entity->showVisible(window);
    }
}

void Map::addEntities(std::vector<std::unique_ptr<MapEntity>> &entities)
{
    for(int i = 0; i < entities.size(); ++i)
        addEntity(entities[i]);
}

void Map::addEntity(std::unique_ptr<MapEntity> &entity_ptr)
{
    m_entities.emplace_back(nullptr);
    m_entities[m_entities.size() - 1].swap(entity_ptr);
}

void Map::draw(Window &window) const
{
    for (const auto &entity : m_entities)
    {
        entity->draw(window);
    }
}

}; // namespace TrafSim