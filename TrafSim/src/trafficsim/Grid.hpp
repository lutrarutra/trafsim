#pragma once

#include <array>

#include <SFML/Graphics.hpp>

#include "Tile.hpp"


namespace ts
{

class Grid : public sf::Drawable
{
public:
    Grid(float tile_size);
    // Initializes all elements of tiles_ to Empty Tile
    // Used to init Grid or clear grid
    void init();

    // Returns nullptr if there is no tile on that index
    Tile *getTile(unsigned int index);
    Tile *getTile(const sf::Vector2f &pos);
    // Returns UINT_MAX if there is no tile on that index
    Tile *getUpNeighbor(unsigned int index);
    Tile *getRightNeighbor(unsigned int index);
    Tile *getDownNeighbor(unsigned int index);
    Tile *getLeftNeighbor(unsigned int index);
    // Gets all neighbors from of tile located at index
    std::array<Tile*, 4> getNeigborTiles(unsigned int index);
    // Returns map's side length    
    unsigned int getSideCount() const { return TileCount; }
    // return 
    std::array<Tile*, 4> getYardTiles(unsigned int index);
    // Returns map total tile count
    unsigned int getTotalTileCount() const { return TileCount * TileCount; }

    // Stores tile in tiles_ array by swapping it with other element at tile->getTileIndex(). 
    // Old tile is destroyed usually
    void swapTile(std::unique_ptr<Tile> &tile);

    // Inherited from sf::Drawable base class
    // Draws all tiles in tiles_
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;


private:
    // TileCount x TileCount tile map
    constexpr static unsigned int TileCount = 50;
    // Length of one side of square Tile
    static float Tile_size;
    
private:
    std::array<std::unique_ptr<Tile>, TileCount * TileCount> tiles_;
    
};
} // namespace ts
