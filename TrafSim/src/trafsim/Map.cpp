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

void Map::addCar(const sf::Vector2f &pos)
{
    auto closest_road = findClosestRoad(pos);
    auto lane_begins = closest_road->getLaneBeginNodes();
    std::shared_ptr<Node> node;
    if (lane_begins.first->getNeighbors().size() > 0)
        node = lane_begins.first;
    else
        node = lane_begins.second;
    Car car(node, node->getNeighbors()[0], {80.f, 80.f});
    m_cars.push_back(car);
}

const std::shared_ptr<Road> Map::findClosestRoad(const sf::Vector2f &pos)
{
    float distance = __FLT_MAX__;
    std::shared_ptr<Road> closest;
    for (const auto &road : m_roads)
    {
        auto endpoints = road->getEndPoints();
        if (distance > VectorMath::Distance(endpoints.first, pos))
        {
            distance = VectorMath::Distance(endpoints.first, pos);
            closest = road;
        }
        if (distance > VectorMath::Distance(endpoints.second, pos))
        {
            distance = VectorMath::Distance(endpoints.second, pos);
            closest = road;
        }
    }
    return closest;
}

void Map::checkIntersections()
{
    // keeps track of created intersections... We only need 1 intesection per 1 road crossing
    std::map<std::pair<int, int>, bool> created;
    for (unsigned int i = 0; i < m_roads.size(); ++i)
    {
        auto r1 = m_roads[i]->getEndPoints();
        for (unsigned int j = 0; j < m_roads.size(); ++j)
        {
            if (i == j || created[{i, j}] || created[{j, i}])
                continue;
            auto r2 = m_roads[j]->getEndPoints();
            auto t = VectorMath::IntersectionPoint(r1.first, r1.second, r2.first, r2.second);
            if (t > 0 && t < 1)
            {
                created[{i, j}] = true;
                m_intersections.emplace_back(m_roads[i], m_roads[j], VectorMath::Lerp(r1.first, r1.second, t));
            }
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

void Map::createRoads(const std::shared_ptr<Node>& begin)
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
    for (const auto &intersection : m_intersections)
        window.draw(intersection);
    for (const auto &car : m_cars)
        window.draw(car);
}

}; // namespace TrafSim