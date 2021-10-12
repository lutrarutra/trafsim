#include "RoadTrisection.hpp"

namespace ts
{

const sf::Texture *RoadTrisection::RightTexture;
const sf::Texture *RoadTrisection::LeftTexture;

RoadTrisection::RoadTrisection(const Tile &tile)
    : RoadTile(tile)
{
    rect_.setTexture(RoadTrisection::RightTexture);
}

void RoadTrisection::connect(std::array<Tile *, 4> &neighbors)
{
    if (dir_.y == 1)
    {
        connectTo(neighbors[UP], DOWN);
        if (right_turn_)
            connectTo(neighbors[RIGHT], LEFT);
        else
            connectTo(neighbors[LEFT], RIGHT);
    }

    else if (dir_.x == 1)
    {
        connectTo(neighbors[RIGHT], LEFT);
        if (right_turn_)
            connectTo(neighbors[DOWN], UP);
        else
            connectTo(neighbors[UP], DOWN);
    }

    else if (dir_.y == -1)
    {
        connectTo(neighbors[DOWN], UP);
        if (right_turn_)
            connectTo(neighbors[LEFT], RIGHT);
        else
            connectTo(neighbors[RIGHT], LEFT);
    }

    else if (dir_.x == -1)
    {
        connectTo(neighbors[LEFT], RIGHT);
        if (right_turn_)
            connectTo(neighbors[UP], DOWN);
        else
            connectTo(neighbors[DOWN], UP);
    }
}

bool RoadTrisection::canConnectTo(NeighborIndex n_index) const
{
    if (n_index == UP)
        return dir_.y == 1 || (right_turn_ && dir_.x == -1) || (!right_turn_ && dir_.x == 1);

    else if (n_index == RIGHT)
        return dir_.x == 1 || (right_turn_ && dir_.y == 1) || (!right_turn_ && dir_.y == -1);

    else if (n_index == DOWN)
        return dir_.y == -1 || (right_turn_ && dir_.x == 1) || (!right_turn_ && dir_.x == -1);

    else if (n_index == LEFT)
        return dir_.x == -1 || (right_turn_ && dir_.y == -1) || (!right_turn_ && dir_.y == 1);

    return false;
}

bool RoadTrisection::connectableFrom(NeighborIndex n_index) const
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

void RoadTrisection::flip()
{
    if (right_turn_)
    {
        rect_.setTexture(RoadTrisection::LeftTexture);
    }
    else
    {
        rect_.setTexture(RoadTrisection::RightTexture);
    }
    dir_ = -dir_;
    right_turn_ = !right_turn_;
}

void RoadTrisection::SetTextures(const sf::Texture *right_texture, const sf::Texture *left_texture)
{
    RoadTrisection::RightTexture = right_texture;
    RoadTrisection::LeftTexture = left_texture;
}

} // namespace ts