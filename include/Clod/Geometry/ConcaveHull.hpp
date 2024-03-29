#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include <Clod/Geometry/Vertex.hpp>
#include <Clod/Geometry/Polycomplex.hpp>

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

        void simplifyCluster(const float &tolerance = 2.f);

        void simplifyConsecutiveVertices(const float &tolerance = 2.f);

        protected:
            [[nodiscard]] int findBestIndexForInsertion(const Vertex &vertexToInsert) const;

        public:
            std::vector<Vertex> vertices;

            explicit ConcaveHull(const std::shared_ptr<sf::Image> &image, const int &alphaTolerance = 5);

            explicit ConcaveHull(const std::vector<Vertex> &vertices);

            void simplify(float tolerance = 2.f, float clusterTolerance = 5.f);

            bool insertVertex(const Vertex &vertex);

            bool insertVertex(const sf::Vector2f &vertex);

            bool insertVertex(const b2Vec2 &vertex);

            void removeVertex(const Vertex &vertex);

            void removeVertex(const sf::Vector2f &vertex);

            void removeVertex(const b2Vec2 &vertex);

            [[nodiscard]] std::vector<Vertex> getVertices() const;

            [[nodiscard]] Polygon getPolygon() const;
    };
}
