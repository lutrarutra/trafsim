#pragma once

#include <vector>
#include <memory>   // std::unique_ptr
#include <climits>  // UINT_MAX

#include "TrafficLight.hpp"

namespace ts
{

class TrafficLightNetwork : public sf::Drawable
{
public:
    TrafficLightNetwork(unsigned int handler_id);

    // return Traffic Light count in this handler
    std::size_t getLightCount() const { return lights_.size(); }
    // Returns all the lights in this handler
    const std::vector<TrafficLight *> &getLights() const { return lights_; }

    // Adds light to handler
    void addLight(TrafficLight *light);
    // Removes light from handler
    void removeLight(void *light_to_remove, const sf::Vector2f &pos);

    // Called from Map once every frame. 
    // Will call update() on active_light_
    void update(float delta_time);

    // Inherited from sf::Drawable
    // Will only draw line between lights in this lights_ to visualize connections
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    const unsigned int handler_id_;
    // index of active light
    unsigned int active_light_ = UINT_MAX;
    std::vector<TrafficLight *> lights_;
    // For drawing connections between lights
    std::vector<sf::Vertex> vertices_;
};

} // namespace ts
