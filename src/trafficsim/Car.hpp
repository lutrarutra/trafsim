#pragma once
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Node.hpp"
#include "TrafficLightNetwork.hpp"
#include "util/VectorMath.hpp"

namespace ts
{

class Car : public sf::Drawable
{
public:
    Car(const std::shared_ptr<Node> &pos, const std::shared_ptr<Node> &dest, const sf::Vector2f &size);

    // Called every frame to move car
    void update(const sf::Time &game_time, float deltatime, const std::vector<std::unique_ptr<Car>> &cars, const std::map<unsigned int, std::unique_ptr<TrafficLightNetwork>> &light_handlers); //deltatime is time from the last update

    // returns true if car is at its destination
    bool isFinished() const { return finished; }

    // Inherited from sf::Drawable, draws shape_
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    // Adds a texture to a std::vector of textures
    static void AddTexture(const sf::Texture *carTexture);

private:
    void findRoute();
    // returns true if there is nothing infront of the car
    // TODO - more efficient collider algorithm eg. raycast
    void calculateVelocity(float deltatime, const std::vector<std::unique_ptr<Car>> &cars, const std::map<unsigned int, std::unique_ptr<TrafficLightNetwork>> &light_handlers);
    
private:
    const std::shared_ptr<Node> pos_, dest_;
    // Tracks previous node
    std::shared_ptr<Node> prev_;
    // Path from beginning node (where car is created) to dest_ node
    std::list<std::shared_ptr<Node>> route_;
    float speed_, acceleration_;
    sf::RectangleShape shape_;
    bool finished = false;
    sf::Vector2f dir_;
    static std::vector<const sf::Texture*> Textures_;

};

} // namespace ts