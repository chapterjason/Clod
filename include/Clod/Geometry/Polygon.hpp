#pragma once

#include <vector>
#include <SFML/System.hpp>

#include "Edge.hpp"

namespace Clod
{
    struct Polygon
    {
        std::vector<sf::Vector2f> vertices;

        explicit Polygon(const std::vector<sf::Vector2f> &vertices);

        [[nodiscard]] std::vector<Edge> getEdges() const;

        [[nodiscard]] bool contains(const Edge &other) const;
    };
}
