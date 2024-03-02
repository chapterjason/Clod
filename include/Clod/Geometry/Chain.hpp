#pragma once

#include <vector>

#include <Clod/Geometry/Edge.hpp>

namespace Clod
{
    class Chain : public std::vector<Edge>
    {
        public:
            Chain(const std::vector<Edge> &edges);

            Chain();

            [[nodiscard]] float length() const;

            [[nodiscard]] std::vector<Vertex> getVertices() const;

            [[nodiscard]] bool contains(const Edge &edge) const;

            [[nodiscard]] bool contains(const Vertex &vertex) const;
    };
}
