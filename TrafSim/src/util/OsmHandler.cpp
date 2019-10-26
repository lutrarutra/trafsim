#include "OsmHandler.hpp"

//This file is partially copied from https://github.com/osmcode/libosmium examples
//But modified to suit for my usage
//All credits to them.

namespace TrafSim
{

OsmHandler::OsmHandler(const std::string &osmfilePath, const Window &window)
    : m_osmfile(osmfilePath.c_str()), m_window(window)
{
}

sf::Vector2f OsmHandler::convert(const osmium::Location &loc) const
{
    float x = (loc.lon() - minlon) / (maxlon - minlon);
    float y = 1 - (loc.lat() - minlat) / (maxlat - minlat);
    return sf::Vector2f(x * m_window.getWidth(), y * m_window.getHeight());
}

//This will handle data from .osm file
struct BuildingHandler : public osmium::handler::Handler
{
    const OsmHandler *instance;
    unique_vector *buildings;

    void way(const osmium::Way &way)
    {
        // Instance of class Building will be owner of this ptr thus responsible for deletion
        const char *buildingTag = way.tags()["building"];
        const char *roadTag = way.tags()["highway"];
        if (buildingTag)
        {
            std::unique_ptr<std::vector<sf::Vertex>> vertices = std::make_unique<std::vector<sf::Vertex>>();
            vertices->reserve(way.nodes().size());
            for (const auto &node : way.nodes())
            {
                vertices->emplace_back(sf::Vector2f(instance->convert(node.location())));
            }
            buildings->push_back(std::make_unique<Building>(vertices));
        }
        else if (roadTag && (strcmp(roadTag, "primary") == 0 || strcmp(roadTag, "secondary") == 0 || strcmp(roadTag, "tertiary") == 0 || strcmp(roadTag, "residential") == 0))
        {
            std::unique_ptr<std::vector<unsigned long long>> refs = std::make_unique<std::vector<unsigned long long>>();
            refs->reserve(way.nodes().size());
            //Road::s_RoadNodes->reserve(way.nodes().size());
            for (const auto &node : way.nodes())
            {
                auto it = Road::s_RoadNodes->find(node.ref());
                (*Road::s_RoadNodes)[node.ref()] = instance->convert(node.location());
                refs->push_back(node.ref());
            }
            buildings->push_back(std::make_unique<Road>(refs));
        }
    }
};

//Takes reference to initialized MapEntity vector
void OsmHandler::FindEntities(unique_vector &buildings) const
{
    using index_type = osmium::index::map::FlexMem<osmium::unsigned_object_id_type, osmium::Location>;
    using location_handler_type = osmium::handler::NodeLocationsForWays<index_type>;
    try
    {
        osmium::io::Reader reader{m_osmfile, osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};

        index_type index;
        location_handler_type location_handler{index};

        BuildingHandler buildingHandler;
        buildingHandler.instance = this;
        buildingHandler.buildings = &buildings;

        osmium::apply(reader, location_handler, buildingHandler);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n";
    }
}

} // namespace TrafSim