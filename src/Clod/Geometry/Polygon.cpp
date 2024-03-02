#include <algorithm>
#include <any>
#include <cmath>
#include <Clod/Geometry/Polygon.hpp>
#include <CDT.h>

#include <Clod/Geometry/Polycomplex.hpp>

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
                const auto distance = vertex.distance(this->vertices[index]);

                if (distance > longestDistance)
                {
                    longestDistance = distance;
                    longestDistanceIndex = index;
                }
            }

            std::ranges::rotate(verticies, verticies.begin() + longestDistanceIndex);
        }

        // find best insertion vertex with lowest disruption
        auto bestEdgeIndex = -1;
        auto minDisruption = std::numeric_limits<float>::max();

        for (auto i = 0; i < verticies.size(); ++i)
        {
            auto currentVertex = verticies[i];
            auto nextVertex = verticies[(i + 1) % verticies.size()];
            auto edge = Edge(currentVertex, nextVertex);

            const auto disruption = edge.disruption(vertex);

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
        this->insertVertices({vertex}, edge);
    }

    void Polygon::insertVertices(const std::vector<Vertex> &others, const Edge &edge)
    {
        if (!this->contains(edge))
        {
            throw std::runtime_error("Polygon does not contain the edge");
        }

        auto vertexA = edge.a;
        auto vertexB = edge.b;
        auto vertexAPosition = this->getVertexIndex(vertexA);
        auto vertexBPosition = this->getVertexIndex(vertexB);

        // Check if vertices are adjacent, and if not, adjust based on their positions
        if (!this->areAdjacent(vertexAPosition, vertexBPosition))
        {
            // If the edge vertices are not adjacent due to being in reverse order,
            if (vertexAPosition > vertexBPosition)
            {
                std::swap(vertexA, vertexB);
                std::swap(vertexAPosition, vertexBPosition);
            }
            // Additional handling can be implemented here if needed
        }

        // Determine the correct position for the new vertex
        int insertPosition;

        // Ensure we insert the vertex in a position that maintains the polygon's integrity
        if (vertexAPosition < vertexBPosition)
        {
            insertPosition = vertexBPosition; // Insert before vertexB if vertexA comes first
        }
        else
        {
            insertPosition = vertexAPosition + 1; // Insert after vertexA if vertexB comes first
        }

        // Insert the new vertices at the determined position
        this->vertices.insert(this->vertices.begin() + insertPosition, others.begin(), others.end());
    }

    bool Polygon::operator==(const Polygon &other) const
    {
        // If the number of vertices is different, the polygons are different
        if (this->vertices.size() != other.vertices.size())
        {
            return false;
        }

        auto equal = true;

        // If any of the vertices are different, the polygons are different
        for (auto index = 0; index < this->vertices.size(); ++index)
        {
            const auto &vertex = this->vertices[index];
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

        for (auto index = 0; index < this->vertices.size(); ++index)
        {
            const auto &vertex = this->vertices[index];
            const auto &nextVertex = this->vertices[(index + 1) % this->vertices.size()];

            edges.emplace_back(vertex, nextVertex);
        }

        return edges;
    }

    bool Polygon::areAdjacent(const int &indexA, const int &indexB) const
    {
        return std::abs(indexA - indexB) == 1 ||
               std::abs(indexA - indexB) == this->vertices.size() - 1;
    }

    bool Polygon::contains(const Edge &other) const
    {
        auto edges = this->getEdges();

        return std::ranges::any_of(edges, [other](const Edge &edge)
        {
            return edge == other;
        });
    }

    bool Polygon::contains(const Vertex &other) const
    {
        return std::ranges::any_of(this->vertices, [other](const Vertex &vertex)
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

    std::vector<Vertex> Polygon::differenceVertices(const Polygon &other, const Edge &edge) const
    {
        auto differenceVertices = std::vector<Vertex>();
        // To remain ordered, we need to rotate "vertices" so that the edge vertices are at the beginning, depending on the edge vertex
        auto copiedVertices = this->vertices;

        // Determine the correct position for the new vertex
        auto vertexA = edge.a;
        auto vertexB = edge.b;
        auto vertexAPosition = this->getVertexIndex(vertexA);
        auto vertexBPosition = this->getVertexIndex(vertexB);

        // Check if vertices are adjacent, and if not, adjust based on their positions
        if (!this->areAdjacent(vertexAPosition, vertexBPosition))
        {
            // If the edge vertices are not adjacent due to being in reverse order,
            if (vertexAPosition > vertexBPosition)
            {
                std::swap(vertexA, vertexB);
                std::swap(vertexAPosition, vertexBPosition);
            }
            // Additional handling can be implemented here if needed
        }

        std::ranges::rotate(copiedVertices, copiedVertices.begin() + vertexAPosition);

        // Find the difference vertices
        for (const auto &vertex: copiedVertices)
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
        auto secondIndex = this->vertices.size() - 1;

        for (auto index = 0; index < this->vertices.size(); index++)
        {
            area += (this->vertices[secondIndex].x + this->vertices[index].x) * (this->vertices[secondIndex].y - this->vertices[index].y);
            secondIndex = index;
        }

        return std::fabs(area / 2.f);
    }

    int Polygon::size() const
    {
        return static_cast<int>(this->vertices.size());
    }

    float Polygon::perimeter() const
    {
        auto perimeter = 0.f;

        for (const auto &edge: this->getEdges())
        {
            perimeter += edge.length();
        }

        return perimeter;
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

    std::shared_ptr<Polycomplex> Polygon::triangulate() const
    {
        std::vector<Polygon> polygons;
        CDT::Triangulation<float> cdt;
        std::vector<CDT::V2d<float>> cdtVertices;
        std::vector<CDT::Edge> edges;

        for (auto index = 0; index < this->vertices.size(); ++index)
        {
            const auto vertex = this->vertices[index];

            cdtVertices.push_back({vertex.x, vertex.y});

            CDT::Edge edge(index, (index + 1) % vertices.size());

            edges.push_back(edge);
        }

        cdt.insertVertices(cdtVertices);
        cdt.insertEdges(edges);
        cdt.eraseOuterTriangles();

        auto cdtTriangles = cdt.triangles;

        for (const auto &cdtTriangle: cdt.triangles)
        {
            auto a = cdt.vertices[cdtTriangle.vertices[0]];
            auto b = cdt.vertices[cdtTriangle.vertices[1]];
            auto c = cdt.vertices[cdtTriangle.vertices[2]];

            polygons.push_back(Polygon({
                                           {a.x, a.y},
                                           {b.x, b.y},
                                           {c.x, c.y}
                                       }));
        }

        return std::make_shared<Polycomplex>(polygons, this->vertices);
    }
}
