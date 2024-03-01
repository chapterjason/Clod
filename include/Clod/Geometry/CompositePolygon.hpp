#pragma once

#include <vector>
#include <set>

#include <Clod/Geometry/Polygon.hpp>

namespace Clod
{
    class CompositePolygon : public std::vector<Polygon>
    {
        std::vector<Vertex> outerVertices;

        [[nodiscard]] int getOuterVertexIndex(const Vertex &vertex) const;

        public:
            CompositePolygon(const vector &polygons, const std::vector<Vertex> &outerVertices);

            [[nodiscard]] std::vector<Polygon> pick(const std::vector<int> &indices) const;

            [[nodiscard]] std::vector<Polygon> pick(const std::set<int> &indices) const;

            [[nodiscard]] std::vector<Vertex> getVertices() const;

            [[nodiscard]] std::vector<Polygon> findAdjacentPolygons(const Polygon &other) const;

            [[nodiscard]] std::vector<Polygon> findAdjacentPolygons(const Edge &other) const;

            [[nodiscard]] std::vector<Polygon> findAdjacentPolygons(const Vertex &other) const;

            [[nodiscard]] std::vector<Edge> getEdges() const;

            [[nodiscard]] std::vector<Edge> getOuterEdges() const;

            [[nodiscard]] std::vector<Edge> getInnerEdges() const;

            [[nodiscard]] std::vector<Edge> getAdjacentEdges(const Edge &other) const;

            [[nodiscard]] std::vector<Edge> getAdjacentEdges(const Vertex &vertex) const;

            [[nodiscard]] std::vector<Edge> getAdjacentEdges(const Edge &other, const Vertex &vertex) const;

            [[nodiscard]] float area() const;

            [[nodiscard]] Vertex centroid() const;
    };
}