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
struct EntityHandler : public osmium::handler::Handler
{
public:
    EntityHandler(const OsmHandler *instance) : m_instance(instance){};

private:
    const OsmHandler *const m_instance;

public:
    unique_vector *entities;
    //Temporary, so we can access roads with just refs
    std::unique_ptr<std::unordered_map<unsigned long long, sf::Vector2f>> road_id_map = std::make_unique<std::unordered_map<unsigned long long, sf::Vector2f>>();
    //temporary, to store roads as refs
    std::unique_ptr<std::vector<unsigned long long>> road_refs = std::make_unique<std::vector<unsigned long long>>();
    //To draw roads
    std::unique_ptr<std::vector<Road>> roads = std::make_unique<std::vector<Road>>();

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
                vertices->emplace_back(sf::Vector2f(m_instance->convert(node.location())));
            }
            entities->push_back(std::make_unique<Building>(vertices));
        }
        else if (roadTag && (strcmp(roadTag, "primary") == 0 || strcmp(roadTag, "secondary") == 0 || strcmp(roadTag, "tertiary") == 0 || strcmp(roadTag, "residential") == 0))
        {
            std::unique_ptr<std::vector<sf::Vertex>> road_vertices = std::make_unique<std::vector<sf::Vertex>>();
            road_vertices->reserve(way.nodes().size());
            road_refs->reserve(way.nodes().size());
            road_id_map->reserve(way.nodes().size() + 1);
            for (const auto &node : way.nodes())
            {
                auto it = road_id_map->find(node.ref());
                (*road_id_map)[node.ref()] = m_instance->convert(node.location());
                road_refs->push_back(node.ref());
                road_vertices->emplace_back(m_instance->convert(node.location()));
            }
            //new road
            road_refs->push_back(0);
            roads->emplace_back(road_vertices);
        }
    }
};

//Takes reference to initialized MapEntity vector
void OsmHandler::FindEntities(unique_vector &entities) const
{
    using index_type = osmium::index::map::FlexMem<osmium::unsigned_object_id_type, osmium::Location>;
    using location_handler_type = osmium::handler::NodeLocationsForWays<index_type>;
    try
    {
        osmium::io::Reader reader{m_osmfile, osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};

        index_type index;
        location_handler_type location_handler{index};

        EntityHandler entityHandler(this);

        //Store entities
        entityHandler.entities = &entities;

        osmium::apply(reader, location_handler, entityHandler);
        //To store all the nodes... TODO - Do we need this?
        std::unique_ptr<std::vector<RoadNode>> roadNodes = std::make_unique<std::vector<RoadNode>>();

        //To make it cleaner to acces elements stored in entityHandler.road_refs
        std::unique_ptr<std::vector<unsigned long long>> refs = std::make_unique<std::vector<unsigned long long>>();
        refs.swap(entityHandler.road_refs);

        for (unsigned int i = 1; i < refs->size(); ++i)
        {
            if (i == 1 || (*refs)[i] == 0)
            {
                //First node of
                roadNodes->push_back(RoadNode((*refs)[i - 1], (*entityHandler.road_id_map)[(*refs)[i - 1]]));
                //Second node
                roadNodes->push_back(RoadNode((*refs)[i], (*entityHandler.road_id_map)[(*refs)[i]], (*roadNodes)[i - 1]));
            }
            // if ref == 0 it means new road
            else if ((*refs)[i] == 0)
            {
            }
            else
            {
                // Add New node
                roadNodes->push_back(RoadNode((*refs)[i], (*entityHandler.road_id_map)[(*refs)[i]], (*roadNodes)[i - 1]));
                // Connect revious node
                (*roadNodes)[i].connect((*roadNodes)[i - 1]);
            }
            // To check connections
            const unsigned long long ref = (*refs)[i];
            for (unsigned int j = 1; j < i; ++j)
            {
                if ((*refs)[j] == ref)
                {
                    (*roadNodes)[j].connect((*roadNodes)[i]);
                }
            }
        }
        //Push back road system
        entities.push_back(std::make_unique<RoadSystem>(roadNodes, entityHandler.roads));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n";
    }
}

} // namespace TrafSim