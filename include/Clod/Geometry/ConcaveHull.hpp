#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include <Clod/Geometry/Vertex.hpp>
#include <Clod/Geometry/CompositePolygon.hpp>

namespace Clod
{
    class ConcaveHull
    {
        void sortVertices();

        void simplifySection(
            const std::vector<Vertex> &vertices,
            int start,
            int end,
            float tolerance,
            std::vector<Vertex> &outVertices
        );

        [[nodiscard]] std::vector<Vertex> simplifyCluster(float tolerance = 2.f) const;

        protected:
            std::vector<Vertex> vertices;

            [[nodiscard]] int findBestIndexForInsertion(const Vertex &vertexToInsert) const;

        public:
            explicit ConcaveHull(const std::shared_ptr<sf::Image> &image, const int &alphaTolerance = 5);

            explicit ConcaveHull(const std::vector<Vertex> &vertexs);

            void simplify(float tolerance = 2.f, float clusterTolerance = 5.f);

            bool insertVertex(const Vertex &vertex);

            void removeVertex(const Vertex &vertex);

            [[nodiscard]] std::vector<Vertex> getVertices() const;

            CompositePolygon getPolygons();
    };
}
