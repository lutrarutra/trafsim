#pragma once

#include <SFML/Graphics.hpp>

namespace TrafSim
{

class Lane
{
public:
    Lane(const sf::Vector2f &begin, const sf::Vector2f &end);

private:
    const sf::Vector2f m_begin, m_end;
};

} // namespace TrafSim
