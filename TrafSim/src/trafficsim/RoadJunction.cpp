#include "RoadJunction.hpp"

namespace ts
{

const sf::Texture *RoadJunction::RightTexture;
const sf::Texture *RoadJunction::LeftTexture;

RoadJunction::RoadJunction(const Tile &tile)
    : RoadTile(tile)
{
    rect_.setTexture(RoadJunction::RightTexture);
}

void RoadJunction::connect(std::array<Tile *, 4> &neighbors)
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

bool RoadJunction::canConnectTo(NeighborIndex n_index) const
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

bool RoadJunction::connectableFrom(NeighborIndex n_index) const
{
    if (n_index == UP)
        return dir_.y == -1 || (dir_.x == -1 && right_turn_) || (dir_.x == 1 && !right_turn_);

    else if (n_index == RIGHT)
        return dir_.x == -1 || (dir_.y == 1 && right_turn_) || (dir_.y == -1 && !right_turn_);

    else if (n_index == DOWN)
        return dir_.y == 1 || (dir_.x == 1 && right_turn_) || (dir_.x == -1 && !right_turn_);

    else if (n_index == LEFT)
        return dir_.x == 1 || (dir_.y == -1 && right_turn_) || (dir_.y == 1 && !right_turn_);

    return false;
}

void RoadJunction::flip()
{
    if (right_turn_)
    {
        rect_.setTexture(RoadJunction::LeftTexture);
    }
    else
    {
        rect_.setTexture(RoadJunction::RightTexture);
    }
    dir_ = -dir_;
    right_turn_ = !right_turn_;
}

void RoadJunction::SetTextures(const sf::Texture *right_texture, const sf::Texture *left_texture)
{
    RoadJunction::RightTexture = right_texture;
    RoadJunction::LeftTexture = left_texture;
}

} // namespace ts