#include <Clod/Geometry/Position.hpp>
#include <cmath>

#include "Clod/Geometry/Vertex.hpp"

namespace Clod
{
    float perpendicularDistance(const Vertex &start, const Vertex &end, const Vertex &vertex)
    {
        const auto normalLength = start.distance(end);
        const auto crossProduct = start.cross(vertex, end);

        return std::fabs(crossProduct) / normalLength;
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
