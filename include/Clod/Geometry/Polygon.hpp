#pragma once

#include <vector>
#include <SFML/System.hpp>

#include <Clod/Geometry/Vertex.hpp>
#include <Clod/Geometry/Edge.hpp>

namespace Clod
{
    struct Polygon
    {
        std::vector<Vertex> vertices;

        explicit Polygon(const std::vector<Vertex> &vertices);

        void addVertex(const Vertex &vertex);

        bool operator==(const Polygon &other) const;

        bool operator!=(const Polygon &other) const;

        [[nodiscard]] std::vector<Edge> getEdges() const;

        [[nodiscard]] bool contains(const Edge &other) const;

        [[nodiscard]] bool contains(const Vertex &other) const;

        [[nodiscard]] std::string toString() const;

        [[nodiscard]] float area() const;

        [[nodiscard]] Vertex centroid() const;
    };
}
