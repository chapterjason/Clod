#include <algorithm>
#include <Clod/Geometry/Polygon.hpp>

namespace Clod
{
    Polygon::Polygon(const std::vector<sf::Vector2f> &vertices)
        : vertices(vertices) {}

    std::vector<Edge> Polygon::getEdges() const
    {
        auto edges = std::vector<Edge>();

        for (auto index = 0; index < vertices.size(); ++index)
        {
            const auto &point = vertices[index];
            const auto &nextPoint = vertices[(index + 1) % vertices.size()];

            edges.emplace_back(point, nextPoint);
        }

        return edges;
    }

    bool Polygon::contains(const Edge &other) const
    {
        auto edges = this->getEdges();

        return std::any_of(edges.begin(), edges.end(), [other](const Edge &edge)
        {
            return edge == other;
        });
    }
}
