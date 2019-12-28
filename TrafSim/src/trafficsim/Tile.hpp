#pragma once

#include <SFML/Graphics.hpp>

#include "util/VectorMath.hpp"
#include "Node.hpp"

namespace ts
{

enum TileCategory
{
    RoadCategory,
    BuildingCategory,
    Empty,
};

enum NeighborIndex
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

class Tile : public sf::Drawable
{
public:
    Tile(const sf::Vector2f &pos, float size, unsigned int tile_index);
    
    virtual TileCategory getCategory() const { return TileCategory::Empty; }
    // TODO: Maybe we don't need nodes for empty tiles?
    // TODO: return raw pointer?
    std::shared_ptr<Node> getNode() const { return node_; }
    // Returns left top corner of the tile
    const sf::Vector2f &getPos() const { return pos_; };
    // Returns center of the tile
    sf::Vector2f getCenter() const;
    // Returns index of the tile
    // This index is position of the tile in Grid's tiles_ std::array
    unsigned int getTileIndex() const { return tile_index_; }
    // Returns side length
    float getSize() const { return size_; }

    // Highlights this tile if selected in MapBuilder
    void selectTile();
    // Highlights this tile if it is under mouse
    void hoverTile();
    // Removes higlightion
    void unSelectTile();
    // Draws Tile
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
    std::shared_ptr<Node> node_;
    sf::Vector2f pos_;
    float size_;
    sf::RectangleShape rect_;
    const unsigned int tile_index_;
};
} // namespace ts
