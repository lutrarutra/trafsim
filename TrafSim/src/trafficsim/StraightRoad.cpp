#include "StraightRoad.hpp"

#include <iostream>

namespace ts
{

const sf::Texture *StraightRoad::Texture;

StraightRoad::StraightRoad(const Tile &tile)
    : RoadTile(tile)
{
    rect_.setTexture(StraightRoad::Texture);
}

void StraightRoad::connect(std::array<Tile *, 4> &neighbors)
{
    if (dir_.y == 1)
        connectTo(neighbors[UP], DOWN);

    else if (dir_.x == 1)
        connectTo(neighbors[RIGHT], LEFT);

    else if (dir_.y == -1)
        connectTo(neighbors[DOWN], UP);

    else if (dir_.x == -1)
        connectTo(neighbors[LEFT], RIGHT);
}

bool StraightRoad::canConnectTo(NeighborIndex n_index) const
{
    if (n_index == UP)
        return dir_.y == 1;

    else if (n_index == RIGHT)
        return dir_.x == 1;

    else if (n_index == DOWN)
        return dir_.y == -1;

    else if (n_index == LEFT)
        return dir_.x == -1;

    return false;
}

bool StraightRoad::connectableFrom(NeighborIndex n_index) const
{
    if (n_index == UP)
        return dir_.y == -1;

    else if (n_index == RIGHT)
        return dir_.x == -1;

    else if (n_index == DOWN)
        return dir_.y == 1;

    else if (n_index == LEFT)
        return dir_.x == 1;

    return false;
}

void StraightRoad::SetTexture(const sf::Texture *texture)
{
    StraightRoad::Texture = texture;
}

} // namespace ts