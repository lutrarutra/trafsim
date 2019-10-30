#pragma once

#include "trafsim/DrawableEntity.hpp"


namespace TrafSim
{

class Car : public DrawableEntity
{
public:
    Car(float lon = 0, float lat = 0);
    virtual void draw(Window& window) const;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::RectangleShape m_rect;
};

};