#include <algorithm>

#include <Clod/Geometry/ConcaveHull.hpp>
#include <Clod/Algorithm/JarvisMarch.hpp>
#include <Clod/Geometry/Polygon.hpp>
#include <Clod/Graphic/Image.hpp>

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

            for (auto i = start + 1; i < end; ++i)
            {
                const auto distance = vertices[start].perpendicularDistance(vertices[end], vertices[i]);

                if (distance > maxDistance)
                {
                    maxDistance = distance;
                    maxIndex = i;
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

    std::vector<Vertex> ConcaveHull::simplifyCluster(const float tolerance) const
    {
        auto clusters = std::vector<Polygon>();
        auto centroids = std::vector<Vertex>();

        // Start with the first vertex in a new cluster
        for (auto &vertex: this->vertices)
        {
            auto foundCluster = false;

            for (auto &cluster: clusters)
            {
                for (const auto &vertexInCluster: cluster.vertices)
                {
                    if (vertex.distance(vertexInCluster) <= tolerance)
                    {
                        cluster.vertices.push_back(vertex);
                        foundCluster = true;
                        break;
                    }
                }

                if (foundCluster)
                {
                    break;
                }
            }

            if (!foundCluster)
            {
                // Start a new cluster with this vertex
                clusters.push_back(Polygon({vertex}));
            }
        }

        // Calculate the centroid for each cluster
        for (const auto &cluster: clusters)
        {
            if (cluster.size() == 1)
            {
                centroids.push_back(cluster.vertices[0]);
            }
            else
            {
                centroids.push_back(cluster.centroid());
            }
        }

        return centroids;
    }

    int ConcaveHull::findBestIndexForInsertion(const Vertex &vertexToInsert) const
    {
        auto longestDistanceIndex = -1;
        auto longestDistance = 0.0f;

        for (auto index = 0; index < this->vertices.size(); ++index)
        {
            const auto distance = vertexToInsert.distance(this->vertices[index]);

            if (distance > longestDistance)
            {
                longestDistance = distance;
                longestDistanceIndex = index;
            }
        }

        auto vertices = this->vertices;

        // Rotate the vertices so that the longest distance is at the beginning
        std::ranges::rotate(vertices, vertices.begin() + longestDistanceIndex);

        // find best edge with lowest disruption in distance and angle
        // distance is weighted more than angle
        auto bestEdgeIndex = -1;
        auto minDisruption = std::numeric_limits<float>::max();

        for (auto index = 0; index < vertices.size(); ++index)
        {
            auto currentVertex = vertices[index];
            auto nextVertex = vertices[(index + 1) % vertices.size()];
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
            this->vertices.insert(this->vertices.begin() + index, vertex);

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
        this->vertices = this->simplifyCluster(clusterTolerance);
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
