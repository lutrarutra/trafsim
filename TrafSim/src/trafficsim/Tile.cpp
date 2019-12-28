#include "Tile.hpp"
#include <iostream>
namespace ts
{
Tile::Tile(const sf::Vector2f &pos, float size, unsigned int tile_index)
    : pos_(pos), size_(size), rect_(sf::Vector2f(size, size)), tile_index_(tile_index)
{
    // Nice green color
    rect_.setOrigin(sf::Vector2f(size_ / 2, size_ / 2));
    rect_.setPosition(pos_ + sf::Vector2f(size_ / 2, size_ / 2));
    rect_.setFillColor(sf::Color(119, 160, 93));
    // rect_.setOutlineThickness(5.f);
    // rect_.setOutlineColor(sf::Color(66, 107, 41));
    node_ = std::make_shared<Node>(pos_ + sf::Vector2f(size_ / 2, size_ / 2));
}

sf::Vector2f Tile::getCenter() const
{
    return pos_ + sf::Vector2f(size_ / 2, size_ / 2);
}

void Tile::selectTile()
{
    sf::Color c = rect_.getFillColor();
    c.a = 100;
    rect_.setFillColor(c);
}

void Tile::hoverTile()
{
    sf::Color c = rect_.getFillColor();
    c.a = 220;
    rect_.setFillColor(c);
}

void Tile::unSelectTile()
{
    sf::Color c = rect_.getFillColor();
    c.a = 255;
    rect_.setFillColor(c);
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect_, states);
    target.draw(*node_, states);
}

} // namespace ts