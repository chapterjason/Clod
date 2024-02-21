#pragma once

#include <SFML/System.hpp>
#include <vector>

namespace Clod
{
    double distance(const sf::Vector2f& a, const sf::Vector2f& b);

    sf::Vector2f centroid(const std::vector<sf::Vector2f>& points);
}
