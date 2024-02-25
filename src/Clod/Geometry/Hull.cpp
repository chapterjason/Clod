#include <algorithm>
#include <Clod/Geometry/Hull.hpp>
#include <Clod/Geometry/Position.hpp>
#include <CDT.h>

#include "Clod/Algorithm/JarvisMarch.hpp"
#include "Clod/Graphic/Image.hpp"

namespace Clod
{
    void Hull::sortPoints()
    {
        auto convex = JarvisMarch(this->points);
        auto interiorPoints = std::vector<sf::Vector2f>();

        for (const auto &point: this->points)
        {
            if (std::find(convex.begin(), convex.end(), point) == convex.end())
            {
                interiorPoints.push_back(point);
            }
        }

        this->points = convex;

        for (auto interiorPoint: interiorPoints)
        {
            this->insertPoint(interiorPoint);
        }
    }

    void Hull::simplifySection( // NOLINT(misc-no-recursion)
        const std::vector<sf::Vector2f> &points,
        const int start,
        const int end,
        const float tolerance,
        std::vector<sf::Vector2f> &outPoints
    )
    {
        if (start < end)
        {
            auto maxIndex = -1;
            float maxDistance = 0.0;

            for (auto i = start + 1; i < end; ++i)
            {
                auto distance = perpendicularDistance(points[start], points[end], points[i]);

                if (distance > maxDistance)
                {
                    maxDistance = distance;
                    maxIndex = i;
                }
            }

            if (maxDistance > tolerance)
            {
                // If the max distance is greater than tolerance, recursively simplify the segments
                this->simplifySection(points, start, maxIndex, tolerance, outPoints);
                this->simplifySection(points, maxIndex, end, tolerance, outPoints);
            }
            else
            {
                // If no point is found with the distance greater than tolerance, add the endpoint
                if (std::find(outPoints.begin(), outPoints.end(), points[start]) == outPoints.end())
                {
                    outPoints.push_back(points[start]);
                }

                outPoints.push_back(points[end]);
            }
        }
    }

    std::vector<sf::Vector2f> Hull::simplifyCluster(const float tolerance) const
    {
        auto clusters = std::vector<std::vector<sf::Vector2f> >();
        auto centroids = std::vector<sf::Vector2f>();

        // Start with the first point in a new cluster
        for (auto &point: this->points)
        {
            auto foundCluster = false;

            for (auto &cluster: clusters)
            {
                for (const auto &pointInCluster: cluster)
                {
                    if (Clod::distance(point, pointInCluster) <= tolerance)
                    {
                        cluster.push_back(point);
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
                // Start a new cluster with this point
                clusters.push_back({point});
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

    int Hull::findBestEdgeForInsertion(const sf::Vector2f &pointToInsert) const
    {
        auto longestDistanceIndex = -1;
        auto longestDistance = 0.0f;

        for (auto index = 0; index < this->points.size(); ++index)
        {
            auto distance = Clod::distance(pointToInsert, this->points[index]);

            if (distance > longestDistance)
            {
                longestDistanceIndex = index;
            }
        }

        auto points = this->points;

        // Rotate the points so that the longest distance is at the beginning
        std::rotate(points.begin(), points.begin() + longestDistanceIndex, points.end());

        // find best edge with lowest disruption in distance and angle
        // distance is weighted more than angle
        auto bestEdgeIndex = -1;
        auto minDisruption = std::numeric_limits<float>::max();

        for (auto i = 0; i < points.size(); ++i)
        {
            auto currentPoint = points[i];
            auto nextPoint = points[(i + 1) % points.size()];

            auto disruption = Clod::disruption(currentPoint, nextPoint, pointToInsert);

            if (disruption < minDisruption)
            {
                minDisruption = disruption;
                bestEdgeIndex = i;
            }
        }

        return bestEdgeIndex;
    }

    Hull::Hull(const std::shared_ptr<sf::Image> &image)
    {
        this->points = detectEdges(image);

        this->sortPoints();
    }

    Hull::Hull(const std::vector<sf::Vector2f> &points)
    {
        this->points = points;

        this->sortPoints();
    }

    bool Hull::insertPoint(const sf::Vector2f &point)
    {
        const auto index = this->findBestEdgeForInsertion(point);

        if (index != -1)
        {
            this->points.insert(this->points.begin() + index, point);

            return true;
        }

        return false;
    }

    void Hull::removePoint(const sf::Vector2f &point)
    {
        const auto index = std::find(this->points.begin(), this->points.end(), point);

        this->points.erase(index);
    }

    void Hull::simplify(
        const float tolerance,
        const float clusterTolerance
    )
    {
        std::vector<sf::Vector2f> simplifiedPoints;

        simplifySection(this->points, 0, static_cast<int>(this->points.size()) - 1, tolerance, simplifiedPoints);

        this->points = simplifiedPoints;
        this->points = this->simplifyCluster(clusterTolerance);
    }

    std::vector<std::vector<sf::Vector2f> > Hull::triangulate()
    {
        CDT::Triangulation<float> cdt;

        std::vector<CDT::V2d<float> > cdtPoints;
        std::vector<CDT::Edge> edges;

        auto index = 0;
        for (const auto &point: points)
        {
            cdtPoints.push_back({point.x, point.y});

            CDT::Edge edge(index, (index + 1) % points.size());

            edges.push_back(edge);

            index++;
        }

        cdt.insertVertices(cdtPoints);
        cdt.insertEdges(edges);
        cdt.eraseOuterTriangles();

        auto cdtTriangles = cdt.triangles;
        auto triangles = std::vector<std::vector<sf::Vector2f> >();

        for (const auto &cdtTriangle: cdt.triangles)
        {
            auto a = cdt.vertices[cdtTriangle.vertices[0]];
            auto b = cdt.vertices[cdtTriangle.vertices[1]];
            auto c = cdt.vertices[cdtTriangle.vertices[2]];
            auto triangle = std::vector<sf::Vector2f>();

            triangle.emplace_back(a.x, a.y);
            triangle.emplace_back(b.x, b.y);
            triangle.emplace_back(c.x, c.y);

            triangles.push_back(triangle);
        }

        return triangles;
    }

    const std::vector<sf::Vector2f> &Hull::getPoints() const
    {
        return this->points;
    }
}
