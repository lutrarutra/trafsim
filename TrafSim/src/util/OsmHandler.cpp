#include "OsmHandler.hpp"

//This file is partially copied from https://github.com/osmcode/libosmium examples
//But modified to suit for my usage
//All credits to them.

#include <osmium/util/progress_bar.hpp>

#include <algorithm>

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
    std::vector<std::unique_ptr<MapEntity>> *entities;
    //Temporary, so we can access roads with just refs
    std::unordered_map<unsigned long long, sf::Vector2f> road_id_map;
    //temporary, to store roads as refs
    std::vector<unsigned long long> road_refs;
    std::vector<sf::Vertex> road_vertices;

    void way(const osmium::Way &way)
    {
        // Instance of class Building will be owner of this ptr thus responsible for deletion
        const char *buildingTag = way.tags()["building"];
        const char *roadTag = way.tags()["highway"];

        if (buildingTag)
        {
            std::vector<sf::Vertex> vertices;
            vertices.reserve(way.nodes().size());
            for (const auto &node : way.nodes())
            {
                vertices.emplace_back(sf::Vector2f(m_instance->convert(node.location())));
            }
            entities->push_back(std::make_unique<Building>(vertices));
        }
        else if (roadTag && (strcmp(roadTag, "primary") == 0 || strcmp(roadTag, "secondary") == 0 || strcmp(roadTag, "tertiary") == 0 || strcmp(roadTag, "residential") == 0))
        {
            //So we can store vertices and give them to Road's constructor
            road_vertices.reserve(way.nodes().size());
            road_refs.reserve(way.nodes().size());
            road_id_map.reserve(way.nodes().size() + 1);
            sf::Vector2f prev = sf::Vector2f(0, 0);

            for (const auto &node : way.nodes())
            {
                road_id_map[node.ref()] = m_instance->convert(node.location());
                road_refs.push_back(node.ref());
                if (!(prev.x == 0 && prev.y == 0))
                {
                    road_vertices.emplace_back(prev);
                    road_vertices.emplace_back(m_instance->convert(node.location()));
                }
                prev = m_instance->convert(node.location());
            }
            road_refs.push_back(0);
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

        std::cout << "VERTICES:" << entityHandler.counter << "\n";
        //To store all the nodes... TODO - Do we need this?
        std::vector<std::shared_ptr<RoadNode>> roadNodes;

        //To make it cleaner to acces elements stored in entityHandler.road_refs
        std::vector<unsigned long long> refs;
        refs = std::move(entityHandler.road_refs);

        //Temporary, to store all used references so we can combine duplicate nodes into one node
        std::map<unsigned long long, std::shared_ptr<RoadNode>> used_refs;

        //First node
        if (refs.size() < 1)
            return;

        std::shared_ptr<RoadNode> previous_node = nullptr;
        for (unsigned int i = 0; i < refs.size(); ++i)
        {
            // 0 means new road
            unsigned long long current_reference = refs[i];
            if (current_reference == 0)
            {
                previous_node = nullptr;
                std::cout << (float)i / refs.size() << "\n";
            }
            else
            {
                if (auto duplicate = used_refs.find(current_reference); duplicate != used_refs.end())
                {
                    //It is duplicate
                    if (previous_node != nullptr)
                        previous_node->connect(duplicate->second);
                    previous_node = duplicate->second;
                }
                else
                {
                    //Its unique
                    auto new_node = std::make_shared<RoadNode>(RoadNode(current_reference, entityHandler.road_id_map[current_reference]));
                    roadNodes.push_back(new_node);
                    if (previous_node != nullptr)
                        previous_node->connect(new_node);
                    used_refs[current_reference] = new_node;
                    previous_node = new_node;
                }
            }
        }
        //Push back road system
        std::cout << "Nodes: " << roadNodes.size() << "\n";
        std::cout << "Vertices " << entityHandler.road_vertices.size() << "\n";
        entities.push_back(std::make_unique<RoadSystem>(roadNodes, entityHandler.road_vertices));
        //reader.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n";
    }
}

} // namespace TrafSim