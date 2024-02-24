#pragma once

#include <SFML/System.hpp>
#include <vector>

namespace Clod
{
    namespace Internal
    {
        void RamerDouglasPeuckerLoop(
            const std::vector<sf::Vector2f> &path,
            double curveThreshold,
            std::vector<sf::Vector2f> &result,
            int beginIndex,
            int endIndex
        );
    }

    std::vector<sf::Vector2f> RamerDouglasPeucker(const std::vector<sf::Vector2f> &path, double curveThreshold);
}
