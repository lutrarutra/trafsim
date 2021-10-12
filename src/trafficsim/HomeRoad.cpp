#include "HomeRoad.hpp"

#include <iostream>

namespace ts
{

const sf::Texture *HomeRoad::Texture;

HomeRoad::HomeRoad(const Tile &tile)
    : RoadTile(tile)
{
    rect_.setTexture(HomeRoad::Texture);
}

void HomeRoad::connect(std::array<Tile *, 4> &neighbors)
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

bool HomeRoad::canConnectTo(NeighborIndex n_index) const
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

bool HomeRoad::connectableFrom(NeighborIndex n_index) const
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

void HomeRoad::SetTexture(const sf::Texture *texture)
{
    HomeRoad::Texture = texture;
}

} // namespace ts