#pragma once

#include <SFML/Graphics.hpp>

#include "RoadTile.hpp"

namespace ts
{

class StraightRoad : public RoadTile
{
public:
    StraightRoad(const Tile &tile);
    virtual RoadType getType() const { return RoadType::StraightRoadType; }

    virtual void connect(std::array<Tile *, 4> &neighbors);

    virtual bool connectableFrom(NeighborIndex n_index) const;
    virtual bool canConnectTo(NeighborIndex n_index) const;

    static void SetTexture(const sf::Texture *texture);

private:
    const static sf::Texture *Texture;
};
} // namespace ts