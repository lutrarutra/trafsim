#pragma once

#include <SFML/Graphics.hpp>


namespace TrafSim
{

class Car : public sf::Drawable
{
public:
    Car();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::RectangleShape m_rect;
};

};