#include "TrafficLightNetwork.hpp"

#include <iostream>

namespace ts
{

TrafficLightNetwork::TrafficLightNetwork(unsigned int handler_id)
    : handler_id_(handler_id)
{
}

void TrafficLightNetwork::addLight(TrafficLight *light)
{
    lights_.push_back(light);
    active_light_ = 0;
    vertices_.emplace_back(light->getPos(), sf::Color::Cyan);
}

void TrafficLightNetwork::removeLight(void *light_to_remove, const sf::Vector2f &pos)
{
    lights_.erase(std::remove_if(lights_.begin(), lights_.end(), [&light_to_remove](const auto &light_element) -> bool {
                      return light_to_remove == light_element;
                  }),
                  lights_.end());

    vertices_.erase(std::remove_if(vertices_.begin(), vertices_.end(), [&pos](const auto &light_vertex) -> bool {
                        return (pos.x == light_vertex.position.x && pos.y == light_vertex.position.y);
                    }),
                    vertices_.end());
}

void TrafficLightNetwork::update(float delta_time)
{
    // this means that there is no light added to this object
    if (lights_.size() < 1)
        return;
    if (active_light_ >= lights_.size())
        active_light_ = 0;
    lights_.at(active_light_)->update(delta_time);
    // While current light is active we can't change other lights
    if (lights_.at(active_light_)->isActivated())
        return;

    // Change active light
    if (active_light_ + 1 < lights_.size())
        active_light_++;
    else
        active_light_ = 0;

    lights_.at(active_light_)->activate();
}

void TrafficLightNetwork::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(&vertices_[0], vertices_.size(), sf::LineStrip, states);
}

} // namespace ts
