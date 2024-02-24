#include <cmath>
#include <Clod/Algorithm/RamerDouglasPeucker.hpp>

#include "Clod/Geometry/Position.hpp"

namespace Clod
{
    namespace Internal
    {
        void RamerDouglasPeuckerLoop(
            const std::vector<sf::Vector2f> &path,
            const double curveThreshold,
            std::vector<sf::Vector2f> &result,
            const int beginIndex,
            const int endIndex
        )
        {
            if (endIndex <= beginIndex + 1)
            {
                // not enough points to simplify
                return;
            }

            auto longestDistance = 0.0;
            auto indexWithLongestDistance = 0;
            for (auto i = beginIndex + 1; i < endIndex; ++i)
            {
                const auto distance = perpendicularDistance(path[beginIndex], path[endIndex], path[i]);

                if (distance > longestDistance)
                {
                    indexWithLongestDistance = i;
                    longestDistance = distance;
                }
            }

            if (longestDistance > curveThreshold)
            {
                // Simplify the segments before and after the current point
                RamerDouglasPeuckerLoop(path, curveThreshold, result, beginIndex, indexWithLongestDistance);
                result.push_back(path[indexWithLongestDistance]); // include the current point in the result
                RamerDouglasPeuckerLoop(path, curveThreshold, result, indexWithLongestDistance, endIndex);
            }
        }
    }

    std::vector<sf::Vector2f> RamerDouglasPeucker(const std::vector<sf::Vector2f> &path, double curveThreshold)
    {
        // Can't simplify a path with less than 3 points
        if (path.size() < 3)
        {
            return path;
        }

        std::vector<sf::Vector2f> result;
        result.push_back(path.front()); // always keep the first point
        Internal::RamerDouglasPeuckerLoop(path, curveThreshold, result, 0, static_cast<int>(path.size()) - 1);
        result.push_back(path.back()); // always keep the last point

        return result;
    }
}
