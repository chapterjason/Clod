#include <Clod/Geometry/Chain.hpp>

#include <ranges>

namespace Clod
{
    Chain::Chain(const std::vector<Edge> &edges)
        : vector(edges) {}

    Chain::Chain()
        : vector() {}

    float Chain::length() const
    {
        auto length = 0.0f;

        for (const auto &edge: *this)
        {
            length += edge.length();
        }

        return length;
    }

    std::vector<Vertex> Chain::getVertices() const
    {
        auto vertices = std::vector<Vertex>();

        for (const auto &edge: *this)
        {
            vertices.push_back(edge.a);
        }

        return vertices;
    }

    bool Chain::contains(const Edge &edge) const
    {
        return std::ranges::any_of(*this, [edge](const Edge &other)
        {
            return other == edge;
        });
    }

    bool Chain::contains(const Vertex &vertex) const
    {
        return std::ranges::any_of(*this, [vertex](const Edge &edge)
        {
            return edge.contains(vertex);
        });
    }
}
