#include <cmath>
#include <Clod/Algorithm/RamerDouglasPeucker.hpp>

#include <Clod/Geometry/Position.hpp>

namespace Clod
{
    namespace Internal
    {
        void RamerDouglasPeuckerLoop(
            const std::vector<Vertex> &path,
            const double curveThreshold,
            std::vector<Vertex> &result,
            const int beginIndex,
            const int endIndex
        )
        {
            if (endIndex <= beginIndex + 1)
            {
                // not enough vertices to simplify
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
                // Simplify the segments before and after the current vertex
                RamerDouglasPeuckerLoop(path, curveThreshold, result, beginIndex, indexWithLongestDistance);
                result.push_back(path[indexWithLongestDistance]); // include the current vertex in the result
                RamerDouglasPeuckerLoop(path, curveThreshold, result, indexWithLongestDistance, endIndex);
            }
        }
    }

    std::vector<Vertex> RamerDouglasPeucker(const std::vector<Vertex> &path, double curveThreshold)
    {
        // Can't simplify a path with less than 3 vertices
        if (path.size() < 3)
        {
            return path;
        }

        std::vector<Vertex> result;
        result.push_back(path.front()); // always keep the first vertex
        Internal::RamerDouglasPeuckerLoop(path, curveThreshold, result, 0, static_cast<int>(path.size()) - 1);
        result.push_back(path.back()); // always keep the last vertex

        return result;
    }
}
