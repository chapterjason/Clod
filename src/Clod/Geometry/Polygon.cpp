#include <algorithm>
#include <any>
#include <cmath>
#include <Clod/Geometry/Polygon.hpp>
#include "Clod/Geometry/Position.hpp"

namespace Clod
{
    Polygon::Polygon(const std::vector<Vertex> &vertices)
        : vertices(vertices) {}

    int Polygon::getVertexIndex(const Vertex &vertex) const
    {
        for (auto index = 0; index < this->vertices.size(); ++index)
        {
            if (this->vertices[index] == vertex)
            {
                return index;
            }
        }

        return -1;
    }

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

    void Polygon::insertVertex(const Vertex &vertex, const Edge &edge)
    {
        if (!this->contains(edge))
        {
            throw std::runtime_error("Polygon does not contain the edge");
        }

        const auto vertexA = edge.a;
        const auto vertexB = edge.b;
        const auto vertexAPosition = this->getVertexIndex(vertexA);
        const auto vertexBPosition = this->getVertexIndex(vertexB);

        if (vertexAPosition < vertexBPosition)
        {
            this->vertices.insert(this->vertices.begin() + vertexAPosition, vertex);
        }
        else
        {
            this->vertices.insert(this->vertices.begin() + vertexBPosition, vertex);
        }
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

    bool Polygon::contains(const Vertex &other) const
    {
        return std::any_of(vertices.begin(), vertices.end(), [other](const Vertex &vertex)
        {
            return vertex == other;
        });
    }

    bool Polygon::isConcave() const
    {
        auto foundPositive = false;
        auto foundNegative = false;

        for (auto index = 0; index < this->vertices.size(); index++)
        {
            Vertex a = this->vertices[index];
            Vertex b = this->vertices[(index + 1) % this->vertices.size()];
            Vertex c = this->vertices[(index + 2) % this->vertices.size()];

            const auto crossSign = a.crossSign(b, c);

            if (crossSign > 0)
            {
                foundPositive = true;
            }
            else if (crossSign < 0)
            {
                foundNegative = true;
            }

            if (foundPositive && foundNegative)
            {
                return true; // The polygon is concave
            }
        }

        return false; // The polygon is convex
    }

    std::vector<Edge> Polygon::intersectEdges(const Polygon &other) const
    {
        auto intersectEdges = std::vector<Edge>();

        for (const auto &edge: this->getEdges())
        {
            if (other.contains(edge))
            {
                intersectEdges.push_back(edge);
            }
        }

        return intersectEdges;
    }

    std::vector<Edge> Polygon::differenceEdges(const Polygon &other) const
    {
        auto differenceEdges = std::vector<Edge>();

        for (const auto &edge: this->getEdges())
        {
            if (!other.contains(edge))
            {
                differenceEdges.push_back(edge);
            }
        }

        return differenceEdges;
    }

    std::vector<Edge> Polygon::symmetricDifferenceEdges(const Polygon &other) const
    {
        auto symmetricDifferenceEdges = std::vector<Edge>();

        for (const auto &edge: this->getEdges())
        {
            if (!other.contains(edge))
            {
                symmetricDifferenceEdges.push_back(edge);
            }
        }

        for (const auto &edge: other.getEdges())
        {
            if (!this->contains(edge))
            {
                symmetricDifferenceEdges.push_back(edge);
            }
        }

        return symmetricDifferenceEdges;
    }

    std::vector<Vertex> Polygon::intersectVertices(const Polygon &other) const
    {
        auto intersectVertices = std::vector<Vertex>();

        for (const auto &vertex: this->vertices)
        {
            if (other.contains(vertex))
            {
                intersectVertices.push_back(vertex);
            }
        }

        return intersectVertices;
    }

    std::vector<Vertex> Polygon::differenceVertices(const Polygon &other) const
    {
        auto differenceVertices = std::vector<Vertex>();

        for (const auto &vertex: this->vertices)
        {
            if (!other.contains(vertex))
            {
                differenceVertices.push_back(vertex);
            }
        }

        return differenceVertices;
    }

    std::vector<Vertex> Polygon::symmetricDifferenceVertices(const Polygon &other) const
    {
        auto symmetricDifferenceVertices = std::vector<Vertex>();

        for (const auto &vertex: this->vertices)
        {
            if (!other.contains(vertex))
            {
                symmetricDifferenceVertices.push_back(vertex);
            }
        }

        for (const auto &vertex: other.vertices)
        {
            if (!this->contains(vertex))
            {
                symmetricDifferenceVertices.push_back(vertex);
            }
        }

        return symmetricDifferenceVertices;
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
