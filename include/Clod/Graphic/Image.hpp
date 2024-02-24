#pragma once

#include <SFML/Graphics.hpp>

namespace Clod
{
    std::vector<sf::Vector2f> detectEdges(const std::shared_ptr<sf::Image> &image);
}
