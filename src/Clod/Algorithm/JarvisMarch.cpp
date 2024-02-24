#include <Clod/Algorithm/JarvisMarch.hpp>

#include <Clod/Geometry/Position.hpp>

namespace Clod
{
    std::vector<sf::Vector2f> JarvisMarch(const std::vector<sf::Vector2f> &points)
    {
        const auto size = points.size();

        std::vector<sf::Vector2f> convexHull;

        auto leftmostIndex = 0;
        for (auto i = 1; i < size; ++i)
        {
            if (points[i].x < points[leftmostIndex].x)
            {
                leftmostIndex = i;
            }
        }

        // Start from leftmost point, keep moving counterclockwise until reaching the start point again
        auto currentPointIndex = leftmostIndex, nextPointIndex = 0;
        do
        {
            // Add current point to result
            convexHull.push_back(points[currentPointIndex]);

            // Searching for a point 'nextPointIndex' such that orientation is
            // counterclockwise for all points 'x'. The idea is to keep track of last visited most counterclock-wise point in nextPointIndex.
            nextPointIndex = (currentPointIndex + 1) % size;
            for (auto i = 0; i < size; ++i)
            {
                // If i is more counterclockwise than current nextPointIndex, then update nextPointIndex
                if (orientation(points[currentPointIndex], points[i], points[nextPointIndex]) == 2)
                {
                    nextPointIndex = i;
                }
            }

            // Now nextPointIndex is the most counterclockwise with respect to currentPointIndex
            // Set currentPointIndex as nextPointIndex for the next iteration, so that nextPointIndex is added to the hull
            currentPointIndex = nextPointIndex;
        } while (currentPointIndex != leftmostIndex); // While we don't come to the first point

        return convexHull;
    }
}
