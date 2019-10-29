#pragma once

#include <osmium/osm/location.hpp>

#include "Window.hpp"

namespace TrafSim
{

//TODO - combine this and drawable
class MapEntity
{
public:
    MapEntity(float lon = 0, float lat = 0);
    virtual void draw(Window &window) const = 0;
    virtual void showVisible(const Window &window) = 0;
    virtual void zoomVertices(const Window &window) = 0;
    virtual unsigned int getVertexCount() const = 0;
    virtual ~MapEntity() = default;

private:
};
}; // namespace TrafSim