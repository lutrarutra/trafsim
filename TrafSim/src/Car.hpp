#pragma once

#include "MapEntity.hpp"

namespace TrafSim
{

class Car : public MapEntity
{
public:
    Car(float lon = 0, float lat = 0);
    virtual void draw(Window& window_) const;
    virtual void scale(float scale);
private:
    sf::RectangleShape rect_;
};

};