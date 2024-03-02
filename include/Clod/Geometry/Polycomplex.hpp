#pragma once

#include <vector>
#include <set>

#include <Clod/Geometry/Polygon.hpp>
#include <Clod/Geometry/Chain.hpp>

namespace Clod
{
    class Polycomplex : public std::vector<Polygon>
    {
        std::vector<Vertex> outerVertices;

        [[nodiscard]] int getOuterVertexIndex(const Vertex &vertex) const;

        public:
            Polycomplex(const vector &polygons, const std::vector<Vertex> &outerVertices);

            void remove(const Polygon &other);

            [[nodiscard]] bool contains(const Polygon &other) const;

            [[nodiscard]] bool contains(const Edge &other) const;

            [[nodiscard]] bool contains(const Vertex &other) const;

            [[nodiscard]] std::vector<Polygon> pick(const std::vector<int> &indices) const;

            [[nodiscard]] std::vector<Polygon> pick(const std::set<int> &indices) const;

            [[nodiscard]] std::vector<Vertex> getVertices() const;

            [[nodiscard]] std::vector<Polygon> findAdjacentPolygons(const Polygon &other) const;

            [[nodiscard]] std::vector<Polygon> findAdjacentPolygons(const Edge &other) const;

            [[nodiscard]] std::vector<Polygon> findAdjacentPolygons(const Edge &edgeA, const Edge &edgeB) const;

            [[nodiscard]] std::vector<Polygon> findAdjacentPolygons(const Edge &edgeA, const Edge &edgeB, const Edge &edgeC) const;

            [[nodiscard]] std::vector<Polygon> findAdjacentPolygons(const Vertex &other) const;

            [[nodiscard]] std::vector<Polygon> findAdjacentPolygons(const Vertex &vertexA, const Vertex &vertexB) const;

            [[nodiscard]] std::vector<Polygon> findAdjacentPolygons(const Vertex &vertexA, const Vertex &vertexB, const Vertex &vertexC) const;

            [[nodiscard]] std::vector<Edge> getEdges() const;

            [[nodiscard]] Chain getOuterEdges() const;

            [[nodiscard]] std::vector<Edge> getInnerEdges() const;

            [[nodiscard]] std::vector<Edge> getAdjacentEdges(const Edge &other) const;

            [[nodiscard]] std::vector<Edge> getAdjacentEdges(const Vertex &vertex) const;

            [[nodiscard]] std::vector<Edge> getAdjacentEdges(const Edge &other, const Vertex &vertex) const;

            [[nodiscard]] float area() const;

            [[nodiscard]] Vertex centroid() const;
    };
}
