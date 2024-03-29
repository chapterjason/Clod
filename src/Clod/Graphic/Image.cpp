#include <Clod/Graphic/Image.hpp>

#include <algorithm>

#include <Clod/Geometry/Vertex.hpp>

namespace Clod
{
    namespace Internal
    {
        // Add a vertex to the list if it doesn't already exist
        void addVertex(std::vector<Vertex> &vertices, const int x, const int y)
        {
            const auto vertex = Vertex(x, y);

            if (std::ranges::find(vertices, vertex) == vertices.end())
            {
                vertices.push_back(vertex);
            }
        }
    }

    std::vector<Vertex> detectEdges(const std::shared_ptr<sf::Image> &image, const int &alphaTolerance)
    {
        auto vertices = std::vector<Vertex>{};

        const auto sizes = image->getSize();
        const auto width = sizes.x;
        const auto height = sizes.y;

        auto inside = false;

        // top to bottom and left to right
        for (auto y = 1; y < height - 1; y++)
        {
            for (auto x = 1; x < width - 1; x++)
            {
                const auto pixel = image->getPixel(sf::Vector2u(x, y));

                if (!inside && pixel.a > alphaTolerance)
                {
                    Internal::addVertex(vertices, x, y);
                    inside = true;
                }
                else if (inside && pixel.a > alphaTolerance)
                {
                    // Look ahead for transparency
                    auto restTransparent = true;

                    for (auto nx = x + 1; nx < width; nx++)
                    {
                        const auto npx = image->getPixel(sf::Vector2u(nx, y));

                        if (npx.a > alphaTolerance)
                        {
                            restTransparent = false;
                            break;
                        }
                    }

                    if (restTransparent)
                    {
                        Internal::addVertex(vertices, x, y);
                        inside = false;
                    }
                }
            }

            // Reset for next row
            inside = false;
        }

        // left to right and top to bottom
        for (auto x = 1; x < width - 1; x++)
        {
            for (auto y = 1; y < height - 1; y++)
            {
                const auto pixel = image->getPixel(sf::Vector2u(x, y));

                if (!inside && pixel.a > alphaTolerance)
                {
                    Internal::addVertex(vertices, x, y);
                    inside = true;
                }
                else if (inside && pixel.a > alphaTolerance)
                {
                    // Look ahead for transparency
                    auto restTransparent = true;

                    for (auto ny = y + 1; ny < height; ny++)
                    {
                        const auto npy = image->getPixel(sf::Vector2u(x, ny));

                        if (npy.a > alphaTolerance)
                        {
                            restTransparent = false;
                            break;
                        }
                    }

                    if (restTransparent)
                    {
                        Internal::addVertex(vertices, x, y);
                        inside = false;
                    }
                }
            }

            // Reset for next column
            inside = false;
        }

        return vertices;
    }
}
