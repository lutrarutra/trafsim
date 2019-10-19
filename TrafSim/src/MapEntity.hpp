#pragma once

#include <osmium/osm/location.hpp>

#include "Window.hpp"

namespace TrafSim
{
class MapEntity
{
public:
    MapEntity(float lon = 0, float lat = 0);
    const osmium::Location& get_loc() const { return loc_; }
    void set_loc(float lon, float lat);
    virtual void draw(const Window& window_) const = 0;
private:
    osmium::Location loc_;
};
}; // namespace TrafSim