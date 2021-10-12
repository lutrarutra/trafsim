#include "RoadTile.hpp"

#include <iostream>

namespace ts
{

RoadTile::RoadTile(const Tile &tile)
    : Tile(tile.getPos(), tile.getSize(), tile.getTileIndex()), dir_(1, 0)
{
    rect_.setFillColor(sf::Color::White);
    rect_.setOutlineThickness(0.f);
}

void RoadTile::addLight(unsigned int handler_id, float green_time)
{
    light_ = std::make_unique<TrafficLight>(pos_, dir_, size_, handler_id, green_time);
}

unsigned int RoadTile::removeLight()
{
    unsigned int handler_id = UINT_MAX;
    if (light_)
        handler_id = light_->getHandlerId();
    light_ = nullptr;
    return handler_id;
}

void RoadTile::autoRotate(std::array<Tile *, 4> &neighbors)
{
    if (neighbors[LEFT] && neighbors[LEFT]->getCategory() == TileCategory::RoadCategory)
    {
        RoadTile *r = static_cast<RoadTile *>(neighbors[LEFT]);
        if (r->canConnectTo(RIGHT))
            return;
    }
    if (neighbors[UP] && neighbors[UP]->getCategory() == TileCategory::RoadCategory)
    {
        RoadTile *r = static_cast<RoadTile *>(neighbors[UP]);
        if (r->canConnectTo(DOWN))
        {
            rotate();
            return;
        }
    }
    if (neighbors[RIGHT] && neighbors[RIGHT]->getCategory() == TileCategory::RoadCategory)
    {
        RoadTile *r = static_cast<RoadTile *>(neighbors[RIGHT]);
        if (r->canConnectTo(LEFT))
        {
            flip();
            return;
        }
    }
    if (neighbors[DOWN] && neighbors[DOWN]->getCategory() == TileCategory::RoadCategory)
    {
        RoadTile *r = static_cast<RoadTile *>(neighbors[DOWN]);
        if (r->canConnectTo(UP))
        {
            rotate();
            flip();
            return;
        }
    }
}

void RoadTile::connectTo(Tile *another, NeighborIndex from)
{
    if (!another || another->getCategory() != TileCategory::RoadCategory)
        return;

    RoadTile *road_tile = static_cast<RoadTile *>(another);
    if (road_tile->connectableFrom(from))
    {
        this->node_->connect(road_tile->getNode());
    }
}

void RoadTile::rotate()
{
    dir_ = sf::Vector2f(dir_.y, -dir_.x);
    rect_.rotate(90);
    if (light_)
        light_->initPos(pos_, dir_, size_);
}

void RoadTile::flip()
{
    rotate();
    rotate();
}

void RoadTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect_, states);
    if (light_)
        target.draw(*light_, states);
}

} // namespace ts