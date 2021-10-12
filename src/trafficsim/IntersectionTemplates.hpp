#pragma once

#include <vector>
#include <iostream>

#include "StraightRoad.hpp"
#include "RoadIntersection.hpp"
#include "RoadJunction.hpp"
#include "RoadTrisection.hpp"

namespace ts
{

enum TemplateType
{
    CrossIntersectionType = 0,
    TIntersectionDownType,
    TIntersectionUpType,
    TIntersectionLeftType,
    TIntersectionRightType,
    RoundaboutLeftType,
    RoundaboutRightType,

    TemplateTypeCount,
};

struct RoadInfo
{
    RoadInfo(int index, sf::Vector2f dir, bool hasLight, RoadType type, bool flipped, sf::Vector2i rel) : index(index), dir(dir), hasLight(hasLight), type(type), flipped(flipped), relative_pos(rel){};

    unsigned int index;
    sf::Vector2f dir;
    bool hasLight;
    RoadType type;
    bool flipped;
    sf::Vector2i relative_pos;
};

class IntersectionTemplates
{
public:
    static std::vector<RoadInfo> GetTiles(TemplateType type, unsigned int index, unsigned int map_side_count)
    {
        if (type == CrossIntersectionType)
        {
            for (unsigned int i = 0; i < cross_intersection_indices_.size(); ++i)
            {
                cross_intersection_indices_[i].index = index + (cross_intersection_indices_[i].relative_pos.x - 1) + (cross_intersection_indices_[i].relative_pos.y - 2) * map_side_count;
            }
            return cross_intersection_indices_;
        }
        else if (type == TIntersectionDownType)
        {
            for (unsigned int i = 0; i < t_intersection_down_indices_.size(); ++i)
            {
                t_intersection_down_indices_[i].index = index + (t_intersection_down_indices_[i].relative_pos.x - 1) + (t_intersection_down_indices_[i].relative_pos.y - 2) * map_side_count;
            }
            return t_intersection_down_indices_;
        }
        else if (type == TIntersectionUpType)
        {
            for (unsigned int i = 0; i < t_intersection_up_indices_.size(); ++i)
            {
                t_intersection_up_indices_[i].index = index + (t_intersection_up_indices_[i].relative_pos.x - 1) + (t_intersection_up_indices_[i].relative_pos.y - 2) * map_side_count;
            }
            return t_intersection_up_indices_;
        }
        else if (type == TIntersectionLeftType)
        {
            for (unsigned int i = 0; i < t_intersection_left_indices_.size(); ++i)
            {
                t_intersection_left_indices_[i].index = index + (t_intersection_left_indices_[i].relative_pos.x - 1) + (t_intersection_left_indices_[i].relative_pos.y - 2) * map_side_count;
            }
            return t_intersection_left_indices_;
        }
        else if (type == TIntersectionRightType)
        {
            for (unsigned int i = 0; i < t_intersection_right_indices_.size(); ++i)
            {
                t_intersection_right_indices_[i].index = index + (t_intersection_right_indices_[i].relative_pos.x - 1) + (t_intersection_right_indices_[i].relative_pos.y - 2) * map_side_count;
            }
            return t_intersection_right_indices_;
        }
        else if (type == RoundaboutLeftType)
        {
            for (unsigned int i = 0; i < roundabout_left_indices_.size(); ++i)
            {
                roundabout_left_indices_[i].index = index + (roundabout_left_indices_[i].relative_pos.x - 1) + (roundabout_left_indices_[i].relative_pos.y - 2) * map_side_count;
            }
            return roundabout_left_indices_;
        }

        else if (type == RoundaboutRightType)
        {
            for (unsigned int i = 0; i < roundabout_right_indices_.size(); ++i)
            {
                roundabout_right_indices_[i].index = index + (roundabout_right_indices_[i].relative_pos.x - 1) + (roundabout_right_indices_[i].relative_pos.y - 2) * map_side_count;
            }
            return roundabout_right_indices_;
        }

        return cross_intersection_indices_;
    }
    static bool CanPlace(TemplateType type, unsigned int index, unsigned int map_side_count)
    {
        if (type == CrossIntersectionType)
        {
            if (index < map_side_count * 2)
                return false;
            if (index > map_side_count * (map_side_count - 1))
                return false;
            if (index % map_side_count >= map_side_count - 2)
                return false;
            if (index % map_side_count == 0)
                return false;
        }
        if (type == TIntersectionDownType || type == TIntersectionUpType || type == TIntersectionLeftType || type == TIntersectionRightType || type == RoundaboutLeftType || type == RoundaboutRightType)
        {
            if (index < map_side_count)
                return false;
            if (index > map_side_count * (map_side_count - 1))
                return false;
            if (index % map_side_count >= map_side_count - 2)
                return false;
            if (index % map_side_count == 0)
                return false;
        }
        return true;
    }

private:
    static std::vector<RoadInfo> cross_intersection_indices_;
    static std::vector<RoadInfo> t_intersection_down_indices_;
    static std::vector<RoadInfo> t_intersection_up_indices_;
    static std::vector<RoadInfo> t_intersection_left_indices_;
    static std::vector<RoadInfo> t_intersection_right_indices_;
    static std::vector<RoadInfo> roundabout_left_indices_;
    static std::vector<RoadInfo> roundabout_right_indices_;
};

} // namespace ts