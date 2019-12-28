#pragma once

#include <climits> // UINT_MAX

#include "Car.hpp"
#include "Grid.hpp"
#include "RoadTile.hpp"
#include "TrafficLightNetwork.hpp"
#include "BuildingHandler.hpp"

namespace ts
{
// This class is abstraction on everything what happens in our simulation
// cars, roads, intersections, building etc are added to a Map
class Map : public sf::Drawable
{
public:
    Map();

    void clearMap();
    void initDay();
    void removeCars() { cars_.clear(); };

    // gets called when app state is changed
    void setSimulating(bool val);

    //Entity handling
    void update(const sf::Time &game_time, float delta_time);

    // Add car to closest Road to "spawn_pos". It's destination will be
    // closest Road to "dest"
    void addCar(const Tile *spawn_pos, const Tile *dest);
    unsigned int addBuilding(BuildingTile *building);

    // For trafficLight handlers
    void removeLight(TrafficLight *light);
    void removeBuilding(unsigned int id);

    void addLight(TrafficLight *light, unsigned int network_id = UINT_MAX);
    void newLightNetwork(TrafficLight *light = nullptr);
    unsigned int getCurrentNetworkId() const { return current_network_id_; }

    //When we add a road we need to call this
    void updateClosestRoads();

    // Inherited from sf::Drawable base class, draws Grid, cars and Traffic Light connections if in editing mode
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    // Returns clocest Node to "pos" which is on the Road.
    std::shared_ptr<Node> closestRoadNode(const sf::Vector2f &pos);
    // Loops over cars_, and deletes all finished cars
    void removeFinishedCars();

public:
    Grid grid_;

private:
    bool simulating_ = false;
    std::vector<std::unique_ptr<Car>> cars_;
    std::map<unsigned int, std::unique_ptr<TrafficLightNetwork>> light_networks_;
    std::map<unsigned int, std::unique_ptr<BuildingHandler>> building_handlers_;
    unsigned int current_network_id_ = 0;
    unsigned int current_building_id_ = 0;
};

} // namespace ts
