#pragma once

#include <osmium/osm/location.hpp>

#include "core/Window.hpp"

namespace TrafSim
{
class MapEntity
{
public:
    MapEntity(float lon = 0, float lat = 0);
    virtual void draw(Window &window) const = 0;
    virtual ~MapEntity() = default;
private:
};
}; // namespace TrafSim