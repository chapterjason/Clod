#include <Clod/Geometry/Polygon.hpp>


Clod::Polygon::Polygon(const std::vector<sf::Vector2f> &vertices): vertices(vertices) {}

Clod::Polygon::Polygon(const std::vector<CDT::V2d<float>> &vertices)
{
    this->vertices.reserve(vertices.size());

    for (const auto &[x, y] : vertices)
    {
        this->vertices.emplace_back(x, y);
    }
}

std::vector<Clod::Edge> Clod::Polygon::edges() const {
    auto edges = std::vector<Edge>();

    for (auto index = 0; index < vertices.size(); ++index)
    {
        const auto &point = vertices[index];
        const auto &nextPoint = vertices[(index + 1) % vertices.size()];

        edges.emplace_back(point, nextPoint);
    }

    return edges;
}
