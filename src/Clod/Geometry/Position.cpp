
#include <Clod/Geometry/Position.hpp>
#include <cmath>

namespace Clod
{
    double distance(const sf::Vector2f& a, const sf::Vector2f& b)
    {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    }

    sf::Vector2f centroid(const std::vector<sf::Vector2f>& points)
    {
        float x = 0;
        float y = 0;

        for (const auto& point : points)
        {
            x += point.x;
            y += point.y;
        }

        x /= static_cast<float>(points.size());
        y /= static_cast<float>(points.size());

        return {x, y};
    }
}
