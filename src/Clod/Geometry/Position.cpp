#include <Clod/Geometry/Position.hpp>
#include <cmath>

namespace Clod
{
    float distance(const sf::Vector2f &a, const sf::Vector2f &b)
    {
        return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
    }

    float squaredDistance(const sf::Vector2f &a, const sf::Vector2f &b)
    {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    }

    float perpendicularDistance(const sf::Vector2f &start, const sf::Vector2f &end, const sf::Vector2f &point)
    {
        const auto normalLength = distance(start, end);
        const auto signedArea  = (point.x - start.x) * (end.y - start.y) - (point.y - start.y) * (end.x - start.x);

        return std::fabs(signedArea ) / normalLength;
    }

    int orientation(const sf::Vector2f &pointA, const sf::Vector2f &pointB, const sf::Vector2f &pointC)
    {
        const auto area = (pointB.y - pointA.y) * (pointC.x - pointB.x) - (pointB.x - pointA.x) * (pointC.y - pointB.y);

        if (area == 0)
        {
            // Collinear
            return 0;
        }

        return (area > 0) ? 1 : 2; // Clockwise or Counter-clockwise
    }

    sf::Vector2f centroid(const std::vector<sf::Vector2f> &points)
    {
        float x = 0;
        float y = 0;

        for (const auto &point: points)
        {
            x += point.x;
            y += point.y;
        }

        x /= static_cast<float>(points.size());
        y /= static_cast<float>(points.size());

        return {x, y};
    }
}
