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

        [[nodiscard]] int getVertexIndex(const Vertex &vertex) const;

        void addVertex(const Vertex &vertex);

        void insertVertex(const Vertex &vertex, const Edge &edge);

        void insertVertices(const std::vector<Vertex> &vertices, const Edge &edge);

        bool operator==(const Polygon &other) const;

        bool operator!=(const Polygon &other) const;

        [[nodiscard]] std::vector<Edge> getEdges() const;

        [[nodiscard]] bool contains(const Edge &other) const;

        [[nodiscard]] bool contains(const Vertex &other) const;

        [[nodiscard]] bool isConcave() const;

        [[nodiscard]] std::vector<Edge> intersectEdges(const Polygon &other) const;

        [[nodiscard]] std::vector<Edge> differenceEdges(const Polygon &other) const;

        [[nodiscard]] std::vector<Edge> symmetricDifferenceEdges(const Polygon &other) const;

        [[nodiscard]] std::vector<Vertex> intersectVertices(const Polygon &other) const;

        [[nodiscard]] std::vector<Vertex> differenceVertices(const Polygon &other) const;

        [[nodiscard]] std::vector<Vertex> symmetricDifferenceVertices(const Polygon &other) const;

        [[nodiscard]] std::string toString() const;

        [[nodiscard]] float area() const;

        [[nodiscard]] Vertex centroid() const;
    };
}
