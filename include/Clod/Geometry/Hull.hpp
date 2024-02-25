#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

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

            [[nodiscard]] int findBestEdgeForInsertion(const sf::Vector2f &pointToInsert) const;

        public:
            explicit Hull(const std::shared_ptr<sf::Image> &image);

            explicit Hull(const std::vector<sf::Vector2f> &points);

            bool insertPoint(const sf::Vector2f &point);

            void removePoint(const sf::Vector2f &point);

            void simplify(float tolerance = 2.f, float clusterTolerance = 5.f);

            std::vector<std::vector<sf::Vector2f> > triangulate();

            [[nodiscard]] const std::vector<sf::Vector2f> &getPoints() const;
    };
}
