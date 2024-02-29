#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Edge.hpp"
#include "Polygon.hpp"

namespace Clod
{
    class Hull
    {
        void sortPoints();

        void simplifySection(
            const std::vector<sf::Vector2f> &points,
            int start,
            int end,
            float tolerance,
            std::vector<sf::Vector2f> &outPoints
        );

        [[nodiscard]] std::vector<sf::Vector2f> simplifyCluster(float tolerance = 2.f) const;

        protected:
            std::vector<sf::Vector2f> points;
            std::vector<Polygon> polygons;
            std::vector<Edge> edges;
            std::vector<Edge> outerEdges;
            std::vector<Edge> innerEdges;

            [[nodiscard]] int findBestEdgeForInsertion(const sf::Vector2f &pointToInsert) const;

        public:
            explicit Hull(const std::shared_ptr<sf::Image> &image, const int &alphaTolerance = 5);

            explicit Hull(const std::vector<sf::Vector2f> &points);

            bool insertPoint(const sf::Vector2f &point);

            void removePoint(const sf::Vector2f &point);

            void simplify(float tolerance = 2.f, float clusterTolerance = 5.f);

            [[nodiscard]] std::vector<Edge> getOuterEdges();

            [[nodiscard]] std::vector<Edge> getInnerEdges();

            [[nodiscard]] std::vector<Edge> getEdges();

            [[nodiscard]] int getPointIndex(const sf::Vector2f &point) const;

            std::vector<Polygon> getPolygons();

            [[nodiscard]] const std::vector<sf::Vector2f> &getPoints() const;

            std::vector<Edge> getEdges(const sf::Vector2f &point);

            std::vector<Edge> getSiblingEdges(const Edge &edge, const sf::Vector2f &point);
    };
}
