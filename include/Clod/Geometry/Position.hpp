#pragma once

#include <SFML/System.hpp>
#include <vector>

namespace Clod
{
    /**
     * Calculates the Euclidean distance between two points in 2D space.
     * This function is useful for determining the straight-line distance
     * between two points (a and b) represented as 2D vectors.
     */
    double distance(const sf::Vector2f &a, const sf::Vector2f &b);

    /**
     * Calculates the squared Euclidean distance between two points in 2D space.
     * This is more performant than calculating the actual Euclidean distance
     * as it avoids the costly square root operation. It's useful in scenarios
     * where relative distances are compared, like in optimization or search
     * algorithms.
     */
    double squaredDistance(const sf::Vector2f &a, const sf::Vector2f &b);

    sf::Vector2f centroid(const std::vector<sf::Vector2f> &points);
}
