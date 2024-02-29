#pragma once

#include <vector>
#include <SFML/System.hpp>
#include <CDT.h>

#include "Edge.hpp"

namespace Clod
{
    struct Polygon
    {
        std::vector<sf::Vector2f> vertices;

        explicit Polygon(const std::vector<sf::Vector2f> &vertices);

        explicit Polygon(const std::vector<CDT::V2d<float>> &vertices);

        [[nodiscard]] std::vector<Edge> edges() const;
    };
}
