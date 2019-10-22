#pragma once

#include <osmium/osm/location.hpp>

#include "Window.hpp"

namespace TrafSim
{
class MapEntity
{
public:
    MapEntity(float lon = 0, float lat = 0);
    const osmium::Location& get_loc() const { return m_loc; }
    void setLoc(float lon, float lat);
    virtual void draw(Window& window_) const = 0;
    virtual void scale(float scale) = 0;
private:
    osmium::Location m_loc;
};
}; // namespace TrafSim