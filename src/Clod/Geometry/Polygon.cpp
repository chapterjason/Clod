#include <Clod/Geometry/Polygon.hpp>

namespace Clod
{
    Polygon::Polygon(const std::vector<sf::Vector2f> &vertices): vertices(vertices) {}

    std::vector<Edge> Polygon::edges() const {
        auto edges = std::vector<Edge>();

        for (auto index = 0; index < vertices.size(); ++index)
        {
            const auto &point = vertices[index];
            const auto &nextPoint = vertices[(index + 1) % vertices.size()];

            edges.emplace_back(point, nextPoint);
        }

        return edges;
    }
}