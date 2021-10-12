#include "RoadTurn.hpp"

namespace ts
{

const sf::Texture *RoadTurn::RightTexture;
const sf::Texture *RoadTurn::LeftTexture;

RoadTurn::RoadTurn(const Tile &tile)
    : RoadTile(tile)
{
    rect_.setTexture(RoadTurn::RightTexture);
}

void RoadTurn::autoRotate(std::array<Tile *, 4> &neighbors)
{
    if (neighbors[DOWN] && neighbors[DOWN]->getCategory() == RoadCategory)
    {
        RoadTile *r = static_cast<RoadTile *>(neighbors[DOWN]);
        if (r->canConnectTo(UP))
            return;
    }
    if (neighbors[UP] && neighbors[UP]->getCategory() == RoadCategory)
    {
        RoadTile *r = static_cast<RoadTile *>(neighbors[UP]);
        if (r->canConnectTo(DOWN))
        {
            rotate();
            rotate();
            return;
        }
    }
    if (neighbors[RIGHT] && neighbors[RIGHT]->getCategory() == RoadCategory)
    {
        RoadTile *r = static_cast<RoadTile *>(neighbors[RIGHT]);
        if (r->canConnectTo(LEFT))
        {
            rotate();
            rotate();
            rotate();
            return;
        }
    }
    if (neighbors[LEFT] && neighbors[LEFT]->getCategory() == RoadCategory)
    {
        RoadTile *r = static_cast<RoadTile *>(neighbors[LEFT]);
        if (r->canConnectTo(RIGHT))
        {
            rotate();
            return;
        }
    }
}

void RoadTurn::connect(std::array<Tile *, 4> &neighbors)
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

bool RoadTurn::canConnectTo(NeighborIndex n_index) const
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

bool RoadTurn::connectableFrom(NeighborIndex n_index) const
{
    if (right_turn_)
    {
        if (n_index == UP)
            return dir_.x == -1;

        else if (n_index == RIGHT)
            return dir_.y == 1;

        else if (n_index == DOWN)
            return dir_.x == 1;

        else if (n_index == LEFT)
            return dir_.y == -1;
    }
    else
    {
        if (n_index == UP)
            return dir_.x == 1;

        else if (n_index == RIGHT)
            return dir_.y == -1;

        else if (n_index == DOWN)
            return dir_.x == -1;

        else if (n_index == LEFT)
            return dir_.y == 1;
    }

    return false;
}

void RoadTurn::flip()
{
    if (right_turn_)
    {
        rect_.setTexture(RoadTurn::LeftTexture);
    }
    else
    {
        rect_.setTexture(RoadTurn::RightTexture);
    }
    dir_ = -dir_;
    right_turn_ = !right_turn_;
}

void RoadTurn::SetTextures(const sf::Texture *right_texture, const sf::Texture *left_texture)
{
    RoadTurn::RightTexture = right_texture;
    RoadTurn::LeftTexture = left_texture;
}

} // namespace ts