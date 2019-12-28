#include "IntersectionTemplates.hpp"

namespace ts
{

std::vector<RoadInfo> IntersectionTemplates::cross_intersection_indices_ = {
    // idnex, dir       haslight    type        flipped     relative_pos
    {0, {0.f, -1.f}, true, StraightRoadType, false, {1, 0}},
    {0, {0.f, 1.f}, false, StraightRoadType, false, {2, 0}},

    {0, {-1.f, 0.f}, false, StraightRoadType, false, {0, 1}},
    {0, {0.f, -1.f}, false, IntersectionType, false, {1, 1}},
    {0, {-1.f, 0.f}, false, IntersectionType, false, {2, 1}},
    {0, {-1.f, 0.f}, true, StraightRoadType, false, {3, 1}},

    {0, {1.f, 0.f}, true, StraightRoadType, false, {0, 2}},
    {0, {1.f, 0.f}, false, IntersectionType, false, {1, 2}},
    {0, {0.f, 1.f}, false, IntersectionType, false, {2, 2}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {3, 2}},

    {0, {0.f, -1.f}, false, StraightRoadType, false, {1, 3}},
    {0, {0.f, 1.f}, true, StraightRoadType, false, {2, 3}},
};

std::vector<RoadInfo> IntersectionTemplates::t_intersection_down_indices_ = {
    // idnex, dir       haslight    type        flipped     relative_pos
    {0, {-1.f, 0.f}, false, StraightRoadType, false, {0, 1}},
    {0, {1.f, 0.f}, false, TrisectionType, true, {1, 1}},
    {0, {1.f, 0.f}, false, JunctionType, true, {2, 1}},
    {0, {-1.f, 0.f}, true, StraightRoadType, false, {3, 1}},

    {0, {1.f, 0.f}, true, StraightRoadType, false, {0, 2}},
    {0, {1.f, 0.f}, false, IntersectionType, false, {1, 2}},
    {0, {0.f, 1.f}, false, IntersectionType, false, {2, 2}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {3, 2}},

    {0, {0.f, -1.f}, false, StraightRoadType, false, {1, 3}},
    {0, {0.f, 1.f}, true, StraightRoadType, false, {2, 3}},
};

std::vector<RoadInfo> IntersectionTemplates::t_intersection_up_indices_ = {
    // idnex, dir       haslight    type        flipped     relative_pos
    {0, {0.f, -1.f}, true, StraightRoadType, false, {1, 0}},
    {0, {0.f, 1.f}, false, StraightRoadType, false, {2, 0}},

    {0, {-1.f, 0.f}, false, StraightRoadType, false, {0, 1}},
    {0, {0.f, -1.f}, false, IntersectionType, false, {1, 1}},
    {0, {-1.f, 0.f}, false, IntersectionType, false, {2, 1}},
    {0, {-1.f, 0.f}, true, StraightRoadType, false, {3, 1}},

    {0, {1.f, 0.f}, true, StraightRoadType, false, {0, 2}},
    {0, {-1.f, 0.f}, false, JunctionType, true, {1, 2}},
    {0, {-1.f, 0.f}, false, TrisectionType, true, {2, 2}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {3, 2}},

};

std::vector<RoadInfo> IntersectionTemplates::t_intersection_left_indices_ = {
    // idnex, dir       haslight    type        flipped     relative_pos
    {0, {0.f, -1.f}, true, StraightRoadType, false, {1, 0}},
    {0, {0.f, 1.f}, false, StraightRoadType, false, {2, 0}},

    {0, {-1.f, 0.f}, false, StraightRoadType, false, {0, 1}},
    {0, {0.f, -1.f}, false, IntersectionType, false, {1, 1}},
    {0, {0.f, -1.f}, false, TrisectionType, true, {2, 1}},

    {0, {1.f, 0.f}, true, StraightRoadType, false, {0, 2}},
    {0, {1.f, 0.f}, false, IntersectionType, false, {1, 2}},
    {0, {0.f, -1.f}, false, JunctionType, true, {2, 2}},

    {0, {0.f, -1.f}, false, StraightRoadType, false, {1, 3}},
    {0, {0.f, 1.f}, true, StraightRoadType, false, {2, 3}},
};

std::vector<RoadInfo> IntersectionTemplates::t_intersection_right_indices_ = {
    // idnex, dir       haslight    type        flipped     relative_pos
    {0, {0.f, -1.f}, true, StraightRoadType, false, {0, 0}},
    {0, {0.f, 1.f}, false, StraightRoadType, false, {1, 0}},

    {0, {0.f, 1.f}, false, JunctionType, true, {0, 1}},
    {0, {-1.f, 0.f}, false, IntersectionType, false, {1, 1}},
    {0, {-1.f, 0.f}, true, StraightRoadType, false, {2, 1}},

    {0, {0.f, 1.f}, false, TrisectionType, true, {0, 2}},
    {0, {0.f, 1.f}, false, IntersectionType, false, {1, 2}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {2, 2}},

    {0, {0.f, -1.f}, false, StraightRoadType, false, {0, 3}},
    {0, {0.f, 1.f}, true, StraightRoadType, false, {1, 3}},
};

std::vector<RoadInfo> IntersectionTemplates::roundabout_left_indices_ = {
    // idnex, dir       haslight    type        flipped     relative_pos
    {0, {0.f, -1.f}, true, StraightRoadType, false, {3, 0}},
    {0, {0.f, 1.f}, false, StraightRoadType, false, {4, 0}},

    {0, {1.f, 0.f}, false, RoadTurnType, false, {1, 1}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {2, 1}},
    {0, {-1.f, 0.f}, false, JunctionType, true, {3, 1}},
    {0, {-1.f, 0.f}, false, TrisectionType, true, {4, 1}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {5, 1}},
    {0, {0.f, -1.f}, false, RoadTurnType, false, {6, 1}},

    {0, {0.f, 1.f}, false, StraightRoadType, false, {1, 2}},
    {0, {0.f, -1.f}, false, StraightRoadType, false, {6, 2}},

    {0, {-1.f, 0.f}, false, StraightRoadType, false, {0, 3}},
    {0, {0.f, -1.f}, false, TrisectionType, true, {1, 3}},
    {0, {0.f, 1.f}, false, JunctionType, true, {6, 3}},
    {0, {-1.f, 0.f}, true, StraightRoadType, false, {7, 3}},

    {0, {1.f, 0.f}, true, StraightRoadType, false, {0, 4}},
    {0, {0.f, -1.f}, false, JunctionType, true, {1, 4}},
    {0, {0.f, 1.f}, false, TrisectionType, true, {6, 4}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {7, 4}},

    {0, {0.f, 1.f}, false, StraightRoadType, false, {1, 5}},
    {0, {0.f, -1.f}, false, StraightRoadType, false, {6, 5}},

    {0, {0.f, 1.f}, false, RoadTurnType, false, {1, 6}},
    {0, {-1.f, 0.f}, false, StraightRoadType, false, {2, 6}},
    {0, {1.f, 0.f}, false, TrisectionType, true, {3, 6}},
    {0, {1.f, 0.f}, false, JunctionType, true, {4, 6}},
    {0, {-1.f, 0.f}, false, StraightRoadType, false, {5, 6}},
    {0, {-1.f, 0.f}, false, RoadTurnType, false, {6, 6}},

    {0, {0.f, -1.f}, false, StraightRoadType, false, {3, 7}},
    {0, {0.f, 1.f}, true, StraightRoadType, false, {4, 7}},
};

std::vector<RoadInfo> IntersectionTemplates::roundabout_right_indices_ = {
    // idnex, dir       haslight    type        flipped     relative_pos
    {0, {0.f, -1.f}, true, StraightRoadType, false, {3, 0}},
    {0, {0.f, 1.f}, false, StraightRoadType, false, {4, 0}},

    {0, {0.f, 1.f}, false, RoadTurnType, true, {1, 1}},
    {0, {-1.f, 0.f}, false, StraightRoadType, false, {2, 1}},
    {0, {-1.f, 0.f}, false, JunctionType, false, {3, 1}},
    {0, {-1.f, 0.f}, false, TrisectionType, false, {4, 1}},
    {0, {-1.f, 0.f}, false, StraightRoadType, false, {5, 1}},
    {0, {1.f, 0.f}, false, RoadTurnType, true, {6, 1}},

    {0, {0.f, -1.f}, false, StraightRoadType, false, {1, 2}},
    {0, {0.f, 1.f}, false, StraightRoadType, false, {6, 2}},

    {0, {-1.f, 0.f}, false, StraightRoadType, false, {0, 3}},
    {0, {0.f, -1.f}, false, TrisectionType, false, {1, 3}},
    {0, {0.f, 1.f}, false, JunctionType, false, {6, 3}},
    {0, {-1.f, 0.f}, true, StraightRoadType, false, {7, 3}},

    {0, {1.f, 0.f}, true, StraightRoadType, false, {0, 4}},
    {0, {0.f, -1.f}, false, JunctionType, false, {1, 4}},
    {0, {0.f, 1.f}, false, TrisectionType, false, {6, 4}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {7, 4}},

    {0, {0.f, -1.f}, false, StraightRoadType, false, {1, 5}},
    {0, {0.f, 1.f}, false, StraightRoadType, false, {6, 5}},

    {0, {-1.f, 0.f}, false, RoadTurnType, true, {1, 6}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {2, 6}},
    {0, {1.f, 0.f}, false, TrisectionType, false, {3, 6}},
    {0, {1.f, 0.f}, false, JunctionType, false, {4, 6}},
    {0, {1.f, 0.f}, false, StraightRoadType, false, {5, 6}},
    {0, {0.f, -1.f}, false, RoadTurnType, true, {6, 6}},

    {0, {0.f, -1.f}, false, StraightRoadType, false, {3, 7}},
    {0, {0.f, 1.f}, true, StraightRoadType, false, {4, 7}},
};

} // namespace ts