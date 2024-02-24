#include <Clod/Graphic/Image.hpp>

namespace Clod
{
    std::vector<sf::Vector2f> detectEdges(const std::shared_ptr<sf::Image> &image)
    {
        auto points = std::vector<sf::Vector2f>{};

        const auto sizes = image->getSize();
        const auto width = sizes.x;
        const auto height = sizes.y;

        auto inside = false;
        for (auto y = 1; y < height - 1; y++)
        {
            for (auto x = 1; x < width - 1; x++)
            {
                const auto pixel = image->getPixel(sf::Vector2u(x, y));

                if (!inside && pixel != sf::Color::Transparent)
                {
                    points.emplace_back(x, y);
                    inside = true;
                }
                else if (inside && pixel != sf::Color::Transparent)
                {
                    // Look ahead for transparency
                    auto restTransparent = true;

                    for (auto nx = x + 1; nx < width; nx++)
                    {
                        auto npx = image->getPixel(sf::Vector2u(nx, y));

                        if (npx != sf::Color::Transparent)
                        {
                            restTransparent = false;
                            break;
                        }
                    }

                    if (restTransparent)
                    {
                        points.emplace_back(x, y);
                        inside = false;
                    }
                }
            }

            // Reset for next row
            inside = false;
        }

        return points;
    }
}
