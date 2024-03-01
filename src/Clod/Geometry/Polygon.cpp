#include <algorithm>
#include <cmath>
#include <Clod/Geometry/Polygon.hpp>

#include "Clod/Geometry/Position.hpp"

namespace Clod
{
    Polygon::Polygon(const std::vector<Vertex> &vertices)
        : vertices(vertices) {}

    void Polygon::addVertex(const Vertex &vertex)
    {
        auto verticies = this->vertices;

        // rotate the vertices so that the longest distance is at the beginning
        {
            auto longestDistanceIndex = -1;
            auto longestDistance = 0.0f;

            for (auto index = 0; index < this->vertices.size(); ++index)
            {
                auto distance = vertex.distance(this->vertices[index]);

                if (distance > longestDistance)
                {
                    longestDistanceIndex = index;
                }
            }

            std::rotate(verticies.begin(), verticies.begin() + longestDistanceIndex, verticies.end());
        }

        // find best insertion vertex with lowest disruption
        auto bestEdgeIndex = -1;
        auto minDisruption = std::numeric_limits<float>::max();

        for (auto i = 0; i < verticies.size(); ++i)
        {
            auto currentVertex = verticies[i];
            auto nextVertex = verticies[(i + 1) % verticies.size()];

            auto disruption = Clod::disruption(currentVertex, nextVertex, vertex);

            if (disruption < minDisruption)
            {
                minDisruption = disruption;
                bestEdgeIndex = i;
            }
        }

        if (bestEdgeIndex == -1)
        {
            throw std::runtime_error("This should never happen");
        }

        this->vertices.insert(this->vertices.begin() + bestEdgeIndex, vertex);
    }

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
            const auto &vertex = vertices[index];
            const auto &otherVertex = other.vertices[index];

            if (vertex != otherVertex)
            {
                equal = false;
                break;
            }
        }

        return equal;
    }

    bool Polygon::operator!=(const Polygon &other) const
    {
        return !(*this == other);
    }

    std::vector<Edge> Polygon::getEdges() const
    {
        auto edges = std::vector<Edge>();

        for (auto index = 0; index < vertices.size(); ++index)
        {
            const auto &vertex = vertices[index];
            const auto &nextVertex = vertices[(index + 1) % vertices.size()];

            edges.emplace_back(vertex, nextVertex);
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
        auto result = std::string("Polygon: {\n");

        for (const auto &edge: this->getEdges())
        {
            result += "  " + edge.toString() + ",\n";
        }

        result += "}";

        return result;
    }

    float Polygon::area() const
    {
        auto area = 0.f;
        auto secondIndex = vertices.size() - 1;

        for (auto index = 0; index < vertices.size(); index++)
        {
            area += (vertices[secondIndex].x + vertices[index].x) * (vertices[secondIndex].y - vertices[index].y);
            secondIndex = index;
        }

        return std::fabs(area / 2.f);
    }

    Vertex Polygon::centroid() const
    {
        auto centroid = Vertex();

        for (const auto &vertex: this->vertices)
        {
            centroid += vertex;
        }

        return centroid / static_cast<float>(this->vertices.size());
    }
}
