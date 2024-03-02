#include <algorithm>

#include <Clod/Geometry/ConcaveHull.hpp>
#include <Clod/Algorithm/JarvisMarch.hpp>
#include <Clod/Geometry/Polygon.hpp>
#include <Clod/Graphic/Image.hpp>
#include <Clod/Geometry/Cluster.hpp>

namespace Clod
{
    void ConcaveHull::sortVertices()
    {
        auto convex = JarvisMarch(this->vertices);
        auto interiorVertices = std::vector<Vertex>();

        for (const auto &vertex: this->vertices)
        {
            if (std::ranges::find(convex, vertex) == convex.end())
            {
                interiorVertices.push_back(vertex);
            }
        }

        this->vertices = convex;

        for (const auto &interiorVertex: interiorVertices)
        {
            this->insertVertex(interiorVertex);
        }
    }

    void ConcaveHull::simplifySection( // NOLINT(misc-no-recursion)
        const std::vector<Vertex> &vertices,
        const int start,
        const int end,
        const float tolerance,
        std::vector<Vertex> &outVertices
    )
    {
        if (start < end)
        {
            auto maxIndex = -1;
            float maxDistance = 0.0;

            for (auto index = start + 1; index < end; ++index)
            {
                const auto& startVertex = vertices[start];
                const auto& endVertex = vertices[end];
                const auto& currentVertex = vertices[index];

                const auto distance = startVertex.perpendicularDistance(endVertex, currentVertex);

                if (distance > maxDistance)
                {
                    maxDistance = distance;
                    maxIndex = index;
                }
            }

            if (maxDistance > tolerance)
            {
                // If the max distance is greater than tolerance, recursively simplify the segments
                this->simplifySection(vertices, start, maxIndex, tolerance, outVertices);
                this->simplifySection(vertices, maxIndex, end, tolerance, outVertices);
            }
            else
            {
                // If no vertex is found with the distance greater than tolerance, add the endvertex
                if (std::ranges::find(outVertices, vertices[start]) == outVertices.end())
                {
                    outVertices.push_back(vertices[start]);
                }

                outVertices.push_back(vertices[end]);
            }
        }
    }

    void ConcaveHull::simplifyCluster(const float &tolerance)
    {
        const auto clusters = Cluster::findClusters(this->vertices, tolerance);

        this->vertices.clear();

        for (const auto &cluster: clusters)
        {
            this->vertices.push_back(cluster.centroid());
        }
    }

    int ConcaveHull::findBestIndexForInsertion(const Vertex &vertexToInsert) const
    {
        auto bestEdgeIndex = -1;
        auto minDisruption = std::numeric_limits<float>::max();

        for (auto index = 0; index < this->vertices.size(); ++index)
        {
            auto currentVertex = this->vertices[index];
            auto nextVertex = this->vertices[(index + 1) % this->vertices.size()];
            auto edge = Edge(currentVertex, nextVertex);

            const auto disruption = edge.disruption(vertexToInsert);

            if (disruption < minDisruption)
            {
                minDisruption = disruption;
                bestEdgeIndex = index;
            }
        }

        return bestEdgeIndex;
    }

    ConcaveHull::ConcaveHull(const std::shared_ptr<sf::Image> &image, const int &alphaTolerance)
    {
        this->vertices = detectEdges(image, alphaTolerance);
        this->sortVertices();
    }

    ConcaveHull::ConcaveHull(const std::vector<Vertex> &vertices)
    {
        this->vertices = vertices;

        this->sortVertices();
    }

    bool ConcaveHull::insertVertex(const Vertex &vertex)
    {
        const auto index = this->findBestIndexForInsertion(vertex);

        if (index != -1)
        {
            this->vertices.insert(this->vertices.begin() + index + 1, vertex);

            return true;
        }

        return false;
    }

    bool ConcaveHull::insertVertex(const sf::Vector2f &vertex)
    {
        return this->insertVertex(Vertex(vertex));
    }

    bool ConcaveHull::insertVertex(const b2Vec2 &vertex)
    {
        return this->insertVertex(Vertex(vertex));
    }

    void ConcaveHull::removeVertex(const sf::Vector2f &vertex)
    {
        this->removeVertex(Vertex(vertex));
    }

    void ConcaveHull::removeVertex(const b2Vec2 &vertex)
    {
        this->removeVertex(Vertex(vertex));
    }

    void ConcaveHull::removeVertex(const Vertex &vertex)
    {
        this->vertices.erase(std::ranges::find(this->vertices, vertex));
    }

    void ConcaveHull::simplify(
        const float tolerance,
        const float clusterTolerance
    )
    {
        std::vector<Vertex> simplifiedVertices;

        simplifySection(this->vertices, 0, static_cast<int>(this->vertices.size()) - 1, tolerance, simplifiedVertices);

        this->vertices = simplifiedVertices;

        // As the last two vertices are always added, we can simplify them by creating a cluster and replace them with the centroid

        this->simplifyCluster(clusterTolerance);
    }

    Polygon ConcaveHull::getPolygon() const
    {
        return this->vertices;
    }

    std::vector<Vertex> ConcaveHull::getVertices() const
    {
        return this->vertices;
    }
}
