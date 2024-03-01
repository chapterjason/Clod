#include <algorithm>
#include <Clod/Geometry/ConcaveHull.hpp>
#include <Clod/Geometry/Position.hpp>
#include <CDT.h>

#include "Clod/Algorithm/JarvisMarch.hpp"
#include "Clod/Geometry/Polygon.hpp"
#include "Clod/Geometry/CompositePolygon.hpp"
#include "Clod/Graphic/Image.hpp"

namespace Clod
{
    void ConcaveHull::sortVertices()
    {
        auto convex = JarvisMarch(this->vertices);
        auto interiorVertices = std::vector<Vertex>();

        for (const auto &vertex: this->vertices)
        {
            if (std::find(convex.begin(), convex.end(), vertex) == convex.end())
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
                if (std::find(outVertices.begin(), outVertices.end(), vertices[start]) == outVertices.end())
                {
                    outVertices.push_back(vertices[start]);
                }

                outVertices.push_back(vertices[end]);
            }
        }
    }

    std::vector<Vertex> ConcaveHull::simplifyCluster(const float tolerance) const
    {
        auto clusters = std::vector<std::vector<Vertex>>();
        auto centroids = std::vector<Vertex>();

        // Start with the first vertex in a new cluster
        for (auto &vertex: this->vertices)
        {
            auto foundCluster = false;

            for (auto &cluster: clusters)
            {
                for (const auto &vertexInCluster: cluster)
                {
                    if (vertex.distance(vertexInCluster) <= tolerance)
                    {
                        cluster.push_back(vertex);
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
                clusters.push_back({vertex});
            }
        }

        // Calculate the centroid for each cluster
        for (const auto &cluster: clusters)
        {
            if (cluster.size() == 1)
            {
                centroids.push_back(cluster[0]);
            }
            else
            {
                centroids.push_back(centroid(cluster));
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
            auto distance = vertexToInsert.distance(this->vertices[index]);

            if (distance > longestDistance)
            {
                longestDistanceIndex = index;
            }
        }

        auto vertices = this->vertices;

        // Rotate the vertices so that the longest distance is at the beginning
        std::rotate(vertices.begin(), vertices.begin() + longestDistanceIndex, vertices.end());

        // find best edge with lowest disruption in distance and angle
        // distance is weighted more than angle
        auto bestEdgeIndex = -1;
        auto minDisruption = std::numeric_limits<float>::max();

        for (auto i = 0; i < vertices.size(); ++i)
        {
            auto currentVertex = vertices[i];
            auto nextVertex = vertices[(i + 1) % vertices.size()];

            auto disruption = Clod::disruption(currentVertex, nextVertex, vertexToInsert);

            if (disruption < minDisruption)
            {
                minDisruption = disruption;
                bestEdgeIndex = i;
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
        const auto index = std::find(this->vertices.begin(), this->vertices.end(), vertex);

        this->vertices.erase(index);
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

    std::shared_ptr<CompositePolygon> ConcaveHull::getPolygon()
    {
        std::vector<Polygon> polygons;
        CDT::Triangulation<float> cdt;
        std::vector<CDT::V2d<float>> cdtVertices;
        std::vector<CDT::Edge> edges;

        auto index = 0;
        for (const auto &vertex: vertices)
        {
            cdtVertices.push_back({vertex.x, vertex.y});

            CDT::Edge edge(index, (index + 1) % vertices.size());

            edges.push_back(edge);

            index++;
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
                                                 Vertex(a.x, a.y),
                                                 Vertex(b.x, b.y),
                                                 Vertex(c.x, c.y)
                                             }));
        }

        return std::make_shared<CompositePolygon>(polygons, this->vertices);
    }

    std::vector<Vertex> ConcaveHull::getVertices() const
    {
        return this->vertices;
    }
}
