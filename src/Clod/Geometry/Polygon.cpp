#include <algorithm>
#include <Clod/Geometry/Polygon.hpp>

namespace Clod
{
    Polygon::Polygon(const std::vector<sf::Vector2f> &vertices)
        : vertices(vertices) {}

    bool Polygon::operator==(const Polygon &other) const
    {
        // If the number of vertices is different, the polygons are different
        if (vertices.size() != other.vertices.size())
        {
            return false;
        }

        auto equal = true;

        // If any of the vertices are different, the polygons are different
        for (auto index = 0; index < vertices.size(); ++index)
        {
            const auto &point = vertices[index];
            const auto &otherPoint = other.vertices[index];

            if (point != otherPoint)
            {
                equal = false;
                break;
            }
        }

        return equal;
    }

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

    std::string Polygon::toString() const
    {
        auto result = std::string("Polygon: {");

        for (const auto &edge: this->getEdges())
        {
            result += "  " + edge.toString() + ", ";
        }

        result += "}";

        return result;
    }
}
