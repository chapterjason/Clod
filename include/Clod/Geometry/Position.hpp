#pragma once

#include <SFML/System.hpp>
#include <vector>

#include "Vertex.hpp"

namespace Clod
{
    /**
     * Calculates the perpendicular distance between a line segment and a vertex.
     */
    float perpendicularDistance(const Vertex &start, const Vertex &end, const Vertex &vertex);

    /**
     * Returns 0 if collinear, 1 if clockwise, 2 if counter-clockwise.
     */
    int orientation(const Vertex &vertexA, const Vertex &vertexB, const Vertex &vertexC);

    /**
     * Calculates the disruption caused by inserting vertex P between edge A->B.
     */
    float disruption(const Vertex &A, const Vertex &B, const Vertex &P);

    Vertex centroid(const std::vector<Vertex> &vertexs);
}
