#pragma once

#include "RoadTile.hpp"

namespace ts
{
class RoadTurn : public RoadTile
{
public:
    RoadTurn(const Tile &tile);
    virtual RoadType getType() const { return RoadType::RoadTurnType; }

    virtual void flip();
    virtual void connect(std::array<Tile *, 4> &neighbors);
    virtual void autoRotate(std::array<Tile *, 4> &neighbors);

    virtual bool connectableFrom(NeighborIndex n_index) const;
    virtual bool canConnectTo(NeighborIndex n_index) const;

    static void SetTextures(const sf::Texture *right_texture, const sf::Texture *left_texture);

private:
    const static sf::Texture *RightTexture;
    const static sf::Texture *LeftTexture;
};
} // namespace ts