#include "Car.hpp"

namespace TrafSim
{

Car::Car(float lon, float lat)
    : MapEntity(lon, lat), rect_(sf::Vector2f(10.0f, 10.0f))
{
    rect_.setPosition(300, 300);
}

void Car::scale(float scale)
{
    rect_.setScale(scale, scale);
}

void Car::draw(Window &window_) const
{
    window_.draw(rect_);
}

}; // namespace TrafSim