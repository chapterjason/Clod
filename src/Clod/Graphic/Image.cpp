#include <Clod/Graphic/Image.hpp>

#include <algorithm>

namespace Clod
{
    namespace Internal
    {
        // Add a point to the list if it doesn't already exist
        void addPoint(std::vector<sf::Vector2f> &points, const int x, const int y)
        {
            auto point = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));

            if (std::find(points.begin(), points.end(), point) == points.end())
            {
                points.push_back(point);
            }
        }
    }

    std::vector<sf::Vector2f> detectEdges(const std::shared_ptr<sf::Image> &image, const int &alphaTolerance)
    {
        auto points = std::vector<sf::Vector2f>{};

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
                    Internal::addPoint(points, x, y);
                    inside = true;
                }
                else if (inside && pixel.a > alphaTolerance)
                {
                    // Look ahead for transparency
                    auto restTransparent = true;

                    for (auto nx = x + 1; nx < width; nx++)
                    {
                        auto npx = image->getPixel(sf::Vector2u(nx, y));

                        if (npx.a > alphaTolerance)
                        {
                            restTransparent = false;
                            break;
                        }
                    }

                    if (restTransparent)
                    {
                        Internal::addPoint(points, x, y);
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
                    Internal::addPoint(points, x, y);
                    inside = true;
                }
                else if (inside && pixel.a > alphaTolerance)
                {
                    // Look ahead for transparency
                    auto restTransparent = true;

                    for (auto ny = y + 1; ny < height; ny++)
                    {
                        auto npy = image->getPixel(sf::Vector2u(x, ny));

                        if (npy.a > alphaTolerance)
                        {
                            restTransparent = false;
                            break;
                        }
                    }

                    if (restTransparent)
                    {
                        Internal::addPoint(points, x, y);
                        inside = false;
                    }
                }
            }

            // Reset for next column
            inside = false;
        }

        return points;
    }
}
