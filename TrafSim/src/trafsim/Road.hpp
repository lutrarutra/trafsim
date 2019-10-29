#pragma once

#include "trafsim/DrawableEntity.hpp"
#include "trafsim/RoadNode.hpp"

namespace TrafSim
{

class Road : public DrawableEntity
{
public:
    //Takes ownership of vertices
    Road(const std::vector<std::shared_ptr<RoadNode>> nodes, bool visible = false);
    const std::vector<std::shared_ptr<RoadNode>>& getNodes() const { return m_nodes; }
    virtual void zoomVertices(const Window &window);

private:
    const std::vector<std::shared_ptr<RoadNode>> m_nodes;
};
} // namespace TrafSim
