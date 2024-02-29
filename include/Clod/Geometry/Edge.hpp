#pragma once

#include <vector>
#include <SFML/System.hpp>

namespace Clod
{
    struct Edge
    {
        sf::Vector2f a;
        sf::Vector2f b;

        Edge(const sf::Vector2f &a, const sf::Vector2f &b);

        bool operator==(const Edge &other) const;

        [[nodiscard]] bool isInsideVector(const std::vector<Edge> &edges) const;
    };
}
