#include "Map.hpp"

namespace TrafSim
{

Map::Map()
{
}

Map::~Map()
{
    if (running)
        t.join();
}

void Map::checkVisible(const Window &window)
{
    running = true;
    for (auto &entity : m_entities)
    {
        if (entity)
            entity->showVisible(window);
    }
}

void Map::showVisible(const Window &window)
{
    if (running)
    {
        t.join();
        running = false;
    }
    t = std::thread(&Map::checkVisible, std::ref(*this), std::ref(window));
}

void Map::addEntities(std::vector<std::unique_ptr<MapEntity>> &entities)
{
    for (unsigned int i = 0; i < entities.size(); ++i)
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
        if (entity)
            entity->draw(window);
    }
}

}; // namespace TrafSim