#pragma once

#include <SFML/Graphics.hpp>

namespace ts
{

enum LightColor
{
    RED = 0,
    YELLOW,
    GREEN
};

class TrafficLight : public sf::Drawable
{
public:
    TrafficLight(const sf::Vector2f &pos, const sf::Vector2f &dir, float tile_size, unsigned int handler_id, float green_time);

    // Getter for traffic light manager
    bool isActivated() const { return activated_; }

    // Getters for cars
    bool canDrive() const { return can_drive_; }
    unsigned int getHandlerId() const { return handler_id_; }
    const sf::RectangleShape &getBlocker() const { return blocker_; }
    const sf::Vector2f &getPos() const { return shape_.getPosition(); }

    // Called from TrafficLightNetwork when this light is activated
    void update(float delta_time);

    // Called when chaning handler
    void setHandlerId(unsigned int id) { handler_id_ = id; }
    // Called when rotating/flipping
    void initPos(const sf::Vector2f &pos, const sf::Vector2f &dir, float tile_size);

    // called from TrafficLightNetwork once when activating
    void activate();

    // Inherited from sf::Drawable, draws light and blocker
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    // Called once when this has been activated for time equal to green_time_
    void deActivate();
    // Changes color of the light
    void setColor(LightColor color);

public:
    // Time this light spends on green
    // Is public to change from GUI
    float green_time_;

private:
    // This stores in which handler does this light belongs to, can be changed in run time
    unsigned int handler_id_;
    sf::Vector2f pos_;
    // Trafficlight itself which changes colors
    sf::RectangleShape shape_;
    // This blocks cars from moving forward
    sf::RectangleShape blocker_;
    LightColor color_ = RED;
    bool activated_ = false;
    bool can_drive_ = false;

    // For how long each light will be activated
    float yellow_time_ = 1;
    // time in seconds from lights activation
    float activated_for_ = 0;
};

} // namespace ts
