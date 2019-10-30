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
    for (auto &entity : m_entities)
    {
        if (entity)
            entity->updateVisible(window);
    }
}

void Map::updateVisible(const Window &window)
{
    if (running)
    {
        t.join();
        running = false;
    }
    else
    {
        running = true;
        t = std::thread(&Map::checkVisible, std::ref(*this), std::ref(window));
    }
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
    std::lock_guard<std::mutex> lock(vector_mutex);
    for (const auto &ptr : m_entities)
    {
        ptr->draw(window);
    }
}

}; // namespace TrafSim