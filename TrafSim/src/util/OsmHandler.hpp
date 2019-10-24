#pragma once

#include <string>
#include <vector>
#include <iostream> //std::cerr std::cout
#include <memory>

//This file is partially copied from https://github.com/osmcode/libosmium examples
//But modified to suit for my usage
//All credits to them.

// Allow any format of input files (XML, PBF, ...)
#include <osmium/io/any_input.hpp>

// For the osmium::geom::haversine::distance() function
#include <osmium/geom/haversine.hpp>

// For osmium::apply()
#include <osmium/visitor.hpp>

// For the location index. There are different types of indexes available.
// This will work for all input files keeping the index in memory.
#include <osmium/index/map/flex_mem.hpp>

// For the NodeLocationForWays handler
#include <osmium/handler/node_locations_for_ways.hpp>

#include <SFML/Graphics/Vertex.hpp>

#include "trafsim/MapEntity.hpp"
#include "trafsim/Building.hpp"

#define MINLON 25.0439000
#define MAXLAT 60.1962000
#define MAXLON 25.0721000
#define MINLAT 60.1872000

namespace TrafSim
{

class OsmHandler
{
public:
    OsmHandler(const std::string &osmfilePath, const Window& window);
    void FindBuildings(unique_vector &buildings) const;
    sf::Vector2f convert(const osmium::Location &loc) const;
private:
private:
    // TODO - Find bounds from .osm files
    const char *m_osmfile;
    const Window &m_window;
    const double minlon = MINLON;
    const double maxlat = MAXLAT;
    const double maxlon = MAXLON;
    const double minlat = MINLAT;
};
} // namespace TrafSim
