#pragma once

#include <vector>
#include <Clod/Geometry/Vertex.hpp>

namespace Clod
{
    class Cluster : std::vector<Vertex>
    {
        static Cluster searchCluster(std::vector<Vertex> &vertices, const float &tolerance, Cluster cluster = Cluster());

        public:
            Cluster();

            Cluster(vector<Vertex> &&vertices);

            static std::vector<Cluster> findClusters(const std::vector<Vertex> &other, const float &tolerance);

            [[nodiscard]] Vertex centroid() const;

    };
}
