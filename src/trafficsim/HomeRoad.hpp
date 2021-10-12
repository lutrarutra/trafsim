#pragma once

#include <SFML/Graphics.hpp>

#include "RoadTile.hpp"

namespace ts
{

class HomeRoad : public RoadTile
{
public:
    HomeRoad(const Tile &tile);
    virtual RoadType getType() const { return RoadType::HomeRoadType; }

    virtual void connect(std::array<Tile *, 4> &neighbors);

    virtual bool connectableFrom(NeighborIndex n_index) const;
    virtual bool canConnectTo(NeighborIndex n_index) const;

    static void SetTexture(const sf::Texture *texture);

private:
    const static sf::Texture *Texture;
};
} // namespace ts