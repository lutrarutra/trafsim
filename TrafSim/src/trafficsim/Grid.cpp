#include "Grid.hpp"
#include <climits>

namespace ts
{

float Grid::Tile_size;

Grid::Grid(float tile_size)
{
    Grid::Tile_size = tile_size;
    /*
    *
    *   0,                  1,                      2,                      ..., TileCount - 1,
    *   
    *   TileCount,        TileCount + 1,        TileCount + 2,        ..., TileCount * 2 - 1,
    * 
    *   TileCount * 2,    TileCount * 2 + 1,    TileCount * 2 + 2,    ..., TileCount * 3 - 1,
    * 
    * 
    */
   init();
}

void Grid::init()
{
    for (unsigned int i = 0; i < TileCount; ++i)
    {
        for (unsigned int j = 0; j < TileCount; ++j)
        {
            tiles_[i * TileCount + j] = std::make_unique<Tile>(Tile(sf::Vector2f(j * Tile_size, i * Tile_size), Tile_size, i * TileCount + j));
        }
    }
}

void Grid::swapTile(std::unique_ptr<Tile> &tile)
{
    tiles_.at(tile->getTileIndex()).swap(tile);
}

std::array<Tile *, 4> Grid::getNeigborTiles(unsigned int index)
{
    std::array<Tile *, 4> neighbors;
    neighbors[NeighborIndex::UP] = getUpNeighbor(index);
    neighbors[NeighborIndex::RIGHT] = getRightNeighbor(index);
    neighbors[NeighborIndex::DOWN] = getDownNeighbor(index);
    neighbors[NeighborIndex::LEFT] = getLeftNeighbor(index);
    return neighbors;
}

Tile *Grid::getTile(unsigned int index)
{
    if (index < TileCount * TileCount)
        return tiles_[index].get();
    return nullptr;
}

Tile *Grid::getTile(const sf::Vector2f &pos)
{
    if (pos.x < 0 || pos.y < 0 || pos.x > (TileCount * Tile_size) || pos.y > (TileCount * Tile_size))
        return nullptr;

    int j = (pos.x + Tile_size) / Tile_size - 1;
    int i = (pos.y + Tile_size) / Tile_size - 1;
    return tiles_[i * TileCount + j].get();
}

Tile *Grid::getUpNeighbor(unsigned int index)
{
    if (index < TileCount)
        return nullptr;

    return tiles_[index - TileCount].get();
}

Tile *Grid::getRightNeighbor(unsigned int index)
{
    if (index == 0 || (TileCount - 1) % index == 0)
        return nullptr;

    return tiles_[index + 1].get();
}
Tile *Grid::getDownNeighbor(unsigned int index)
{
    if (index + TileCount >= TileCount * TileCount)
        return nullptr;

    return tiles_[index + TileCount].get();
}
Tile *Grid::getLeftNeighbor(unsigned int index)
{
    if (index == 0 || (TileCount) % index == 0)
        return nullptr;

    return tiles_[index - 1].get();
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &tile : tiles_)
        target.draw(*tile, states);
}


} // namespace ts