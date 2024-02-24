#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace Clod
{
    std::vector<sf::Vector2f> detectEdges(const std::shared_ptr<sf::Image> &image);
}
