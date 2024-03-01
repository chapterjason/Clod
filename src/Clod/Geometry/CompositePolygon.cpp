#include <algorithm>
#include <Clod/Geometry/CompositePolygon.hpp>

namespace Clod
{
    int CompositePolygon::getOuterVertexIndex(const Vertex &vertex) const
    {
        for (auto index = 0; index < this->outerVertices.size(); ++index)
        {
            if (this->outerVertices[index] == vertex)
            {
                return index;
            }
        }

        throw std::runtime_error("This should not happen");
    }

    CompositePolygon::CompositePolygon(const vector &polygons, const std::vector<Vertex> &outerVertices)
        : vector(polygons),
          outerVertices(outerVertices) {}

    void CompositePolygon::remove(const Polygon &other)
    {
        this->erase(std::remove(this->begin(), this->end(), other), this->end());
    }

    std::vector<Polygon> CompositePolygon::pick(const std::vector<int> &indices) const
    {
        auto polygons = std::vector<Polygon>();

        for (const auto index: indices)
        {
            polygons.push_back(this->at(index));
        }

        return polygons;
    }

    std::vector<Polygon> CompositePolygon::pick(const std::set<int> &indices) const
    {
        return this->pick(std::vector(indices.begin(), indices.end()));
    }

    std::vector<Vertex> CompositePolygon::getVertices() const
    {
        return this->outerVertices;
    }

    std::vector<Polygon> CompositePolygon::findAdjacentPolygons(const Polygon &other) const
    {
        // get all edges of the polygon and return all polygons which shares the same edge
        auto edges = other.getEdges();
        auto adjacentPolygonIndexes = std::set<int>();

        for (auto index = 0; index < this->size(); ++index)
        {
            const auto polygon = this->at(index);

            // skip the same polygon
            if (polygon == other)
            {
                continue;
            }

            // Compare the edges of the polygons
            for (const auto &edge: polygon.getEdges())
            {
                for (const auto &otherEdge: polygon.getEdges())
                {
                    if (edge == otherEdge)
                    {
                        adjacentPolygonIndexes.insert(index);
                    }
                }
            }
        }

        return this->pick(adjacentPolygonIndexes);
    }

    std::vector<Polygon> CompositePolygon::findAdjacentPolygons(const Edge &other) const
    {
        auto adjacentPolygonIndices = std::set<int>();

        for (auto index = 0; index < this->size(); ++index)
        {
            const auto polygon = this->at(index);

            if (polygon.contains(other))
            {
                adjacentPolygonIndices.insert(index);
            }
        }

        return this->pick(adjacentPolygonIndices);
    }

    std::vector<Polygon> CompositePolygon::findAdjacentPolygons(const Edge &edgeA, const Edge &edgeB) const
    {
        auto adjacentPolygonIndices = std::set<int>();

        for (auto index = 0; index < this->size(); ++index)
        {
            const auto polygon = this->at(index);

            if (polygon.contains(edgeA) && polygon.contains(edgeB))
            {
                adjacentPolygonIndices.insert(index);
            }
        }

        return this->pick(adjacentPolygonIndices);
    }

    std::vector<Polygon> CompositePolygon::findAdjacentPolygons(
        const Edge &edgeA,
        const Edge &edgeB,
        const Edge &edgeC
    ) const
    {
        auto adjacentPolygonIndices = std::set<int>();

        for (auto index = 0; index < this->size(); ++index)
        {
            const auto polygon = this->at(index);

            if (polygon.contains(edgeA) && polygon.contains(edgeB) && polygon.contains(edgeC))
            {
                adjacentPolygonIndices.insert(index);
            }
        }

        return this->pick(adjacentPolygonIndices);
    }

    std::vector<Polygon> CompositePolygon::findAdjacentPolygons(const Vertex &other) const
    {
        auto adjacentPolygonIndices = std::set<int>();

        for (auto index = 0; index < this->size(); ++index)
        {
            const auto polygon = this->at(index);

            for (const auto &edge: polygon.getEdges())
            {
                if (edge.contains(other))
                {
                    adjacentPolygonIndices.insert(index);
                }
            }
        }

        return this->pick(adjacentPolygonIndices);
    }

    std::vector<Polygon> CompositePolygon::findAdjacentPolygons(const Vertex &vertexA, const Vertex &vertexB) const
    {
        auto adjacentPolygonIndices = std::set<int>();

        for (auto index = 0; index < this->size(); ++index)
        {
            const auto polygon = this->at(index);

            for (const auto &edge: polygon.getEdges())
            {
                if (edge.contains(vertexA) && edge.contains(vertexB))
                {
                    adjacentPolygonIndices.insert(index);
                }
            }
        }

        return this->pick(adjacentPolygonIndices);
    }

    std::vector<Polygon> CompositePolygon::findAdjacentPolygons(
        const Vertex &vertexA,
        const Vertex &vertexB,
        const Vertex &vertexC
    ) const
    {
        auto adjacentPolygonIndices = std::set<int>();

        for (auto index = 0; index < this->size(); ++index)
        {
            const auto polygon = this->at(index);

            for (const auto &edge: polygon.getEdges())
            {
                if (edge.contains(vertexA) && edge.contains(vertexB) && edge.contains(vertexC))
                {
                    adjacentPolygonIndices.insert(index);
                }
            }
        }

        return this->pick(adjacentPolygonIndices);
    }

    std::vector<Edge> CompositePolygon::getEdges() const
    {
        auto edges = std::vector<Edge>();

        for (const auto &polygon: *this)
        {
            const auto polygonEdges = polygon.getEdges();

            for (const auto &edge: polygonEdges)
            {
                // prevent duplicates
                if (std::any_of(edges.begin(), edges.end(), [edge](const Edge &other)
                {
                    return edge == other;
                }))
                {
                    continue;
                }

                edges.push_back(edge);
            }
        }

        return edges;
    }

    std::vector<Edge> CompositePolygon::getOuterEdges() const
    {
        auto outerEdges = std::vector<Edge>();

        // Cycle through all outer vertices and create edges
        for (const auto &edge: this->getEdges())
        {
            const auto aIndex = this->getOuterVertexIndex(edge.a);
            const auto bIndex = this->getOuterVertexIndex(edge.b);

            if (aIndex == bIndex + 1 || aIndex == bIndex - 1)
            {
                outerEdges.push_back(edge);
            }
        }

        // Close the hull
        outerEdges.emplace_back(this->outerVertices.back(), this->outerVertices.front());

        return outerEdges;
    }

    std::vector<Edge> CompositePolygon::getInnerEdges() const
    {
        auto innerEdges = std::vector<Edge>();

        const auto outerEdges = this->getOuterEdges();

        for (const auto &edge: this->getEdges())
        {
            if (!edge.isInsideVector(outerEdges))
            {
                innerEdges.push_back(edge);
            }
        }

        return innerEdges;
    }

    std::vector<Edge> CompositePolygon::getAdjacentEdges(const Edge &other) const
    {
        const auto vertexA = other.a;
        const auto vertexB = other.b;

        auto adjacentEdges = std::vector<Edge>();

        for (const auto &edge: this->getEdges())
        {
            // Skip the same edge
            if (edge == other)
            {
                continue;
            }

            if (edge.contains(vertexA) || edge.contains(vertexB))
            {
                adjacentEdges.push_back(edge);
            }
        }

        return adjacentEdges;
    }

    std::vector<Edge> CompositePolygon::getAdjacentEdges(const Vertex &vertex) const
    {
        auto adjacentEdges = std::vector<Edge>();

        for (const auto &edge: this->getEdges())
        {
            if (edge.contains(vertex))
            {
                adjacentEdges.push_back(edge);
            }
        }

        return adjacentEdges;
    }

    std::vector<Edge> CompositePolygon::getAdjacentEdges(const Edge &other, const Vertex &vertex) const
    {
        auto adjacentEdges = std::vector<Edge>();

        for (const auto &edge: this->getAdjacentEdges(other))
        {
            if (edge == other)
            {
                continue;
            }

            if (edge.contains(vertex))
            {
                adjacentEdges.push_back(edge);
            }
        }

        return adjacentEdges;
    }

    float CompositePolygon::area() const
    {
        auto area = 0.f;

        for (const auto &polygon: *this)
        {
            area += polygon.area();
        }

        return area;
    }

    Vertex CompositePolygon::centroid() const
    {
        auto centroid = Vertex();

        for (const auto &polygon: *this)
        {
            centroid += polygon.centroid();
        }

        return centroid / static_cast<float>(this->size());
    }
}
