#include <Clod/Geometry/Position.hpp>
#include <cmath>

#include "Clod/Geometry/Vertex.hpp"

namespace Clod
{
    float perpendicularDistance(const Vertex &start, const Vertex &end, const Vertex &vertex)
    {
        const auto normalLength = start.distance(end);
        const auto signedArea = (vertex.x - start.x) * (end.y - start.y) - (vertex.y - start.y) * (end.x - start.x);

        return std::fabs(signedArea) / normalLength;
    }

    int orientation(const Vertex &vertexA, const Vertex &vertexB, const Vertex &vertexC)
    {
        const auto area = (vertexB.y - vertexA.y) * (vertexC.x - vertexB.x) - (vertexB.x - vertexA.x) * (vertexC.y - vertexB.y);

        if (area == 0)
        {
            // Collinear
            return 0;
        }

        return (area > 0) ? 1 : 2; // Clockwise or Counter-clockwise
    }

    float disruption(const Vertex &A, const Vertex &B, const Vertex &P)
    {
        const auto dAB = A.distance(B);
        const auto dAP = A.distance(P);
        const auto dPB = P.distance(B);

        return dAP + dPB - dAB;
    }

    Vertex centroid(const std::vector<Vertex> &vertices)
    {
        float x = 0;
        float y = 0;

        for (const auto &vertex: vertices)
        {
            x += vertex.x;
            y += vertex.y;
        }

        x /= static_cast<float>(vertices.size());
        y /= static_cast<float>(vertices.size());

        return Vertex(x, y);
    }
}
