#include <Clod/Algorithm/JarvisMarch.hpp>

#include <Clod/Geometry/Position.hpp>
#include <Clod/Geometry/Vertex.hpp>

namespace Clod
{
    std::vector<Vertex> JarvisMarch(const std::vector<Vertex> &vertices)
    {
        const auto size = vertices.size();

        std::vector<Vertex> convexHull;

        auto leftmostIndex = 0;
        for (auto i = 1; i < size; ++i)
        {
            if (vertices[i].x < vertices[leftmostIndex].x)
            {
                leftmostIndex = i;
            }
        }

        // Start from leftmost vertex, keep moving counterclockwise until reaching the start vertex again
        auto currentVertexIndex = leftmostIndex, nextVertexIndex = 0;
        do
        {
            // Add current vertex to result
            convexHull.push_back(vertices[currentVertexIndex]);

            // Searching for a vertex 'nextVertexIndex' such that orientation is
            // counterclockwise for all vertices 'x'. The idea is to keep track of last visited most counterclock-wise vertex in nextVertexIndex.
            nextVertexIndex = (currentVertexIndex + 1) % size;
            for (auto i = 0; i < size; ++i)
            {
                // If i is more counterclockwise than current nextVertexIndex, then update nextVertexIndex
                if (orientation(vertices[currentVertexIndex], vertices[i], vertices[nextVertexIndex]) == 2)
                {
                    nextVertexIndex = i;
                }
            }

            // Now nextVertexIndex is the most counterclockwise with respect to currentVertexIndex
            // Set currentVertexIndex as nextVertexIndex for the next iteration, so that nextVertexIndex is added to the hull
            currentVertexIndex = nextVertexIndex;
        } while (currentVertexIndex != leftmostIndex); // While we don't come to the first vertex

        return convexHull;
    }
}
