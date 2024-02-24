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
    float distance(const sf::Vector2f &a, const sf::Vector2f &b);

    /**
     * Calculates the squared Euclidean distance between two points in 2D space.
     * This is more performant than calculating the actual Euclidean distance
     * as it avoids the costly square root operation. It's useful in scenarios
     * where relative distances are compared, like in optimization or search
     * algorithms.
     */
    float squaredDistance(const sf::Vector2f &a, const sf::Vector2f &b);

    /**
     * Calculates the perpendicular distance between a line segment and a point.
     */
    float perpendicularDistance(const sf::Vector2f &start, const sf::Vector2f &end, const sf::Vector2f &point);

    /**
     * Returns 0 if collinear, 1 if clockwise, 2 if counter-clockwise.
     */
    int orientation(const sf::Vector2f &pointA, const sf::Vector2f &pointB, const sf::Vector2f &pointC);

    sf::Angle angle(const sf::Vector2f &pointA, const sf::Vector2f &pointB);

    sf::Vector2f centroid(const std::vector<sf::Vector2f> &points);
}
