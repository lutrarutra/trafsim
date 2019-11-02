#include "Map.hpp"

namespace TrafSim
{

Map::Map()
{
}

void Map::update(float delta_time)
{
    for (auto &car : m_cars)
    {
        car.update(delta_time);
    }
}

void Map::checkIntersections()
{
    for(unsigned int i = 0; i < m_roads.size(); ++i)
    {
        for(unsigned int j = 0; j < m_roads.size(); ++j)
        {
            if(i == j)
                continue;
            
        }
    }
}

void Map::constructRoads(const std::shared_ptr<Node> &cur, std::shared_ptr<Road> prevRoad, std::map<std::shared_ptr<Node>, bool> &visited)
{
    if (visited[cur])
        return;
    visited[cur] = true;

    for (const auto &neighbor : cur->getNeighbors())
    {
        if (prevRoad == nullptr)
            m_roads.push_back(std::make_shared<Road>(cur, neighbor, 100.f));
        else
            m_roads.push_back(std::make_shared<Road>(*prevRoad, neighbor));

        constructRoads(neighbor, m_roads[m_roads.size() - 1], visited);
    }
}

void Map::createRoads(const std::shared_ptr<Node> begin)
{
    Road *road = nullptr;
    std::shared_ptr<Node> cur = begin;
    std::shared_ptr<Node> prev = nullptr;
    std::map<std::shared_ptr<Node>, bool> visited;
    constructRoads(cur, nullptr, visited);
}

void Map::draw(Window &window) const
{
    for (const auto &road : m_roads)
        window.draw(*road);
}

}; // namespace TrafSim