#include "DataHandler.hpp"
#include "CsvRow.hpp"
#include <fstream>
#include <string>   // std::string
#include <iostream> // std::cout
#include <sstream>  // std::istringstream
#include <stdio.h>

namespace ts
{

void DataHandler::loadTexture(const char *src, const char *texture_key)
{
    textures_.insert(std::make_pair(texture_key, std::make_unique<sf::Texture>()));
    textures_[texture_key]->loadFromFile(src);
}

void DataHandler::loadMap(const char *file_name, MapBuilder &builder, Grid &grid) const
{
    // Dont load ".csv"-file
    if (file_name[0] == '.')
        return;
    try
    {
        std::ifstream file(file_name);
        if (!file.good())
        {
            throw std::ios_base::failure("File not found.");
        }
        // file.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
        builder.clearMap();
        current_file_ = std::string(file_name);

        sf::Vector2f pos, dir, pos_tl;
        int i, j, flipped, istrafficlight;
        float green_time;
        unsigned int handler_id;

        CsvRow row;
        while (file >> row)
        {
            //std::cout << row[0] << row[1] << row[2] << row[3] << row[4] << "\n";

            i = stoi(row[0]);
            j = stoi(row[1]);
            TileCategory tile_category = static_cast<TileCategory>(i);

            if (tile_category == TileCategory::RoadCategory)
            {
                RoadType road_type = static_cast<RoadType>(j);
                pos.x = stof(row[4]);
                pos.y = stof(row[5]);

                dir.x = stoi(row[2]);
                dir.y = stoi(row[3]);

                flipped = stoi(row[6]);

                istrafficlight = stoi(row[7]);

                if (istrafficlight)
                {
                    pos_tl.x = stof(row[8]);
                    pos_tl.y = stof(row[9]);
                    handler_id = stoi(row[10]);
                    green_time = stof(row[11]);
                }

                //add road
                //    StraightRoadType = 0,

                if (road_type == RoadType::StraightRoadType)
                {
                    builder.addRoad(pos, RoadType::StraightRoadType, false);
                }
                else if (road_type == RoadType::RoadTurnType)
                {
                    builder.addRoad(pos, RoadType::RoadTurnType, false);
                }
                else if (road_type == RoadType::HomeRoadType)
                {
                    builder.addRoad(pos, RoadType::HomeRoadType, false);
                }
                else if (road_type == RoadType::IntersectionType)
                {
                    builder.addRoad(pos, RoadType::IntersectionType, false);
                }
                else if (road_type == RoadType::JunctionType)
                {
                    builder.addRoad(pos, RoadType::JunctionType, false);
                }
                else if (road_type == RoadType::TrisectionType)
                {
                    builder.addRoad(pos, RoadType::TrisectionType, false);
                }

                // Direction of the road
                // Up: { 0, 1 }, Right { 1, 0 }, Down { 0, -1 }, Left { -1, 0 }

                //std::cout << dir.x << " " << dir.y << std::endl;
                if (flipped == 0)
                    builder.flipRoad(pos);

                if (dir.x == 1 && flipped == 0)
                {
                    builder.rotateRoad(pos);
                    builder.rotateRoad(pos);
                }
                else if (dir.y == -1)
                {
                    if (flipped == 1)
                    {
                        builder.rotateRoad(pos);
                    }
                    else
                    {
                        builder.rotateRoad(pos);
                        builder.rotateRoad(pos);
                        builder.rotateRoad(pos);
                    }
                }
                else if (dir.x == -1)
                {
                    if (flipped == 1)
                    {
                        builder.rotateRoad(pos);
                        builder.rotateRoad(pos);
                    }
                    else
                    {
                    }
                }
                else if (dir.y == 1)
                {
                    if (flipped == 1)
                    {
                        builder.rotateRoad(pos);
                        builder.rotateRoad(pos);
                        builder.rotateRoad(pos);
                    }
                    else
                    {
                        builder.rotateRoad(pos);
                    }
                }

                //Trafficlights
                if (istrafficlight)
                {
                    auto tile = grid.getTile(pos_tl);
                    RoadTile *road = static_cast<RoadTile *>(tile);
                    builder.addTrafficLight(pos_tl, handler_id, green_time);
                }
            }
            else if (tile_category == TileCategory::BuildingCategory)
            {
                BuildingType building_type = static_cast<BuildingType>(j);
                pos.x = stof(row[4]);
                pos.y = stof(row[5]);

                dir.x = stoi(row[2]);
                dir.y = stoi(row[3]);

                if (building_type == BuildingType::HomeBuildingType)
                {
                    builder.addBuilding(pos, BuildingType::HomeBuildingType);
                }
                else if (building_type == BuildingType::OfficeBuildingType)
                {
                    builder.addBuilding(pos, BuildingType::OfficeBuildingType);
                }
            }
        }
        file.close();
        logs_.emplace_back("File, " + std::string(file_name) + ", loaded succesfully.");
    }
    catch (const std::ios_base::failure &e)
    {
        logs_.emplace_back("Error loading file: " + std::string(file_name));
        std::cerr << "Error loading file: ";
        std::cout << e.what() << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        logs_.emplace_back("File format not supported in file: " + std::string(file_name));
        std::cerr << "File format not supported: ";
        std::cout << e.what() << std::endl;
        builder.clearMap();
    }

    /*
    *   Load map using methods from MapBuilder:
    *   builder.addRoad(), builder.rotateRoad() and .flipRoad()
    */
}

void DataHandler::saveMap(const char *file_name, Grid &grid) const
{

    /*
    *   Use XML or JSON
    *   
    *   Tiles are stored in grid, to access tile you can use grid.getTile(index) ( returns unique_ptr to Tile )
    * 
    *   Indexes go from 0 to grid.getSize()
    * 
    *   To get type of Tile use tile.getType() enum value of TileType
    * 
    *   If tile is not of type Empty convert it with static_cast to RoadTile*
    *   this will allow to get access to getDir() and isFlipped() functions
    *   RoadTile *road = static_cast<RoadTile *>(tile.get());
    * 
    *   to get the position of road use .getPos()
    */
    //if(grid.getTile(0)==NULL)
    //    return 0;
    if (file_name[0] == '.')
        return;

    logs_.emplace_back("Writing to file: " + std::string(file_name));
    //if(!fp)
    //    return 0;

    // TODO save left and right turns and dtraffic lights

    FILE *fp = fopen(file_name, "w");

    for (unsigned int i = 0; i < grid.getSideCount() * grid.getSideCount(); i++)
    {

        //std::cout << pos.x <<" "<< pos.y << std::endl;
        if (grid.getTile(i)->getCategory() == TileCategory::RoadCategory)
        {

            RoadTile *road = static_cast<RoadTile *>(grid.getTile(i));
            if (road->getLight())
            {
                fprintf(fp, "%d,%d,%f,%f,%f,%f,%d,1,%f,%f,%d,%f\n", road->getCategory(), road->getType(), road->getDir().x, road->getDir().y, road->getPos().x, road->getPos().y, road->isFlipped(), road->getLight()->getPos().x, road->getLight()->getPos().y, road->getLight()->getHandlerId(), road->getLight()->green_time_);
            }
            else
            {
                fprintf(fp, "%d,%d,%f,%f,%f,%f,%d,0\n", road->getCategory(), road->getType(), road->getDir().x, road->getDir().y, road->getPos().x, road->getPos().y, road->isFlipped());
            }
        }
        else if (grid.getTile(i)->getCategory() == TileCategory::BuildingCategory)
        {
            BuildingTile *building = static_cast<BuildingTile *>(grid.getTile(i));

            fprintf(fp, "%d,%d,%f,%f,%f,%f\n", building->getCategory(), building->getType(), building->getDir().x, building->getDir().y, building->getPos().x, building->getPos().y);
        }
    }
    fclose(fp);

    logs_.emplace_back("Map saved succesfully to: " + std::string(file_name));
}

void DataHandler::loadTexturesFromFile(const char *src)
{
    std::ifstream file(src);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line.size() < 3)
                continue;

            auto texture_key = line.substr(0, line.find(" "));
            auto file_name = line.substr(line.find(" ") + 1);

            loadTexture(file_name.c_str(), texture_key.c_str());
        }
    }
    else
    {
        std::cout << "File: " << src << " not found." << std::endl;
    }
}

} // namespace ts