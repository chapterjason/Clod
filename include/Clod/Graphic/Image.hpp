#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include <Clod/Geometry/Vertex.hpp>

namespace Clod
{
    std::vector<Vertex> detectEdges(const std::shared_ptr<sf::Image> &image, const int &alphaTolerance = 5);
}
