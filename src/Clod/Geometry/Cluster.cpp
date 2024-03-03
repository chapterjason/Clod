#include <Clod/Geometry/Cluster.hpp>

namespace Clod {
    Cluster Cluster::searchCluster(std::vector<Vertex> &vertices, const float &tolerance, Cluster cluster)
    {
        // If cluster is empty, add the first vertex
        if (cluster.empty())
        {
            if (vertices.empty())
            {
                return cluster;
            }

            cluster.push_back(vertices[0]);
            vertices.erase(vertices.begin());

            return searchCluster(vertices, tolerance, cluster);
        }

        // if cluster is not empty, find the vertex with the lowest distance under the tolerance
        auto minDistance = std::numeric_limits<float>::max();
        Vertex minVertex;

        for (auto &vertex: vertices)
        {
            for (auto &vertexInCluster: cluster)
            {
                const auto distance = vertex.distance(vertexInCluster);

                if (distance < minDistance)
                {
                    minDistance = distance;
                    minVertex = vertex;
                }
            }
        }

        if (minDistance <= tolerance)
        {
            cluster.push_back(minVertex);
            vertices.erase(std::ranges::find(vertices, minVertex));

            return searchCluster(vertices, tolerance, cluster);
        }
        else
        {
            return cluster;
        }
    }

    Cluster::Cluster() {}

    Cluster::Cluster(vector<Vertex> &&vertices): vector<Vertex>(vertices) {}

    std::vector<Cluster> Cluster::findClusters(const std::vector<Vertex> &other, const float &tolerance)
    {
        auto vertices = other;
        auto clusters = std::vector<Cluster>();

        for (auto &vertex: vertices)
        {
            // If the vertex is already in a cluster, skip it
            if (std::ranges::find(vertices, vertex) == vertices.end())
            {
                continue;
            }

            auto cluster = searchCluster(vertices, tolerance);

            if (!cluster.empty())
            {
                clusters.push_back(cluster);
            }
        }

        return clusters;
    }

    Vertex Cluster::centroid() const
    {
        if (this->empty())
        {
            throw std::runtime_error("Cannot calculate the centroid of an empty cluster");
        }

        if (this->size() == 1)
        {
            return this->at(0);
        }

        auto centroid = Vertex();

        for (const auto &vertex: *this)
        {
            centroid += vertex;
        }

        return centroid / static_cast<float>(this->size());
    }
}
