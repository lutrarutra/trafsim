#include "RoadIntersection.hpp"

namespace ts
{

const sf::Texture *RoadIntersection::RightTexture;
const sf::Texture *RoadIntersection::LeftTexture;

RoadIntersection::RoadIntersection(const Tile &tile)
    : RoadTile(tile)
{
    rect_.setTexture(RoadIntersection::RightTexture);
}

void RoadIntersection::connect(std::array<Tile *, 4> &neighbors)
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

bool RoadIntersection::canConnectTo(NeighborIndex n_index) const
{
    if (n_index == UP)
        return dir_.y == 1 || (dir_.x == -1 && right_turn_) || (dir_.x == 1 && !right_turn_);

    else if (n_index == RIGHT)
        return dir_.x == 1 || (dir_.y == 1 && right_turn_) || (dir_.y == -1 && !right_turn_);

    else if (n_index == DOWN)
        return dir_.y == -1 || (dir_.x == 1 && right_turn_) || (dir_.x == -1 && !right_turn_);

    else if (n_index == LEFT)
        return dir_.x == -1 || (dir_.y == -1 && right_turn_) || (dir_.y == 1 && !right_turn_);

    return false;
}

bool RoadIntersection::connectableFrom(NeighborIndex n_index) const
{
    if (n_index == UP)
        return dir_.y == -1 || (dir_.x == 1 && right_turn_) || (dir_.x == -1 && !right_turn_);

    else if (n_index == RIGHT)
        return dir_.x == -1 || (dir_.y == -1 && right_turn_) || (dir_.y == 1 && !right_turn_);

    else if (n_index == DOWN)
        return dir_.y == 1 || (dir_.x == -1 && right_turn_) || (dir_.x == 1 && !right_turn_);

    else if (n_index == LEFT)
        return dir_.x == 1 || (dir_.y == 1 && right_turn_) || (dir_.y == -1 && !right_turn_);

    return false;
}

void RoadIntersection::flip()
{
    if (right_turn_)
    {
        rect_.setTexture(RoadIntersection::LeftTexture);
    }
    else
    {
        rect_.setTexture(RoadIntersection::RightTexture);
    }
    dir_ = -dir_;
    right_turn_ = !right_turn_;
}

void RoadIntersection::SetTextures(const sf::Texture *right_texture, const sf::Texture *left_texture)
{
    RoadIntersection::RightTexture = right_texture;
    RoadIntersection::LeftTexture = left_texture;
}

} // namespace ts