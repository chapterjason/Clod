#pragma once

#include <optional>
#include <SFML/System.hpp>

#include <Clod/Geometry/Vertex.hpp>

namespace Clod
{
    struct Edge
    {
        Vertex a;
        Vertex b;

        Edge(const Vertex &a, const Vertex &b);

        bool operator==(const Edge &other) const;

        bool operator!=(const Edge &other) const;

        [[nodiscard]] bool contains(const Vertex &vertex) const;

        [[nodiscard]] float disruption(const Vertex &vertex) const;

        [[nodiscard]] float length() const;

        [[nodiscard]] sf::Angle direction() const;

        [[nodiscard]] std::optional<sf::Angle> angle(const Edge &other) const;

        [[nodiscard]] Vertex midpoint() const;

        [[nodiscard]] std::string toString() const;
    };
}
