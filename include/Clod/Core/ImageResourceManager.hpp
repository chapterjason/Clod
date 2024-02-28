#pragma once

#include <Clod/Core/ResourceManager.hpp>
#include <SFML/Graphics.hpp>

namespace Clod
{
    class ImageResourceManager : public ResourceManager<sf::Image>
    {
        public:
        std::shared_ptr<sf::Image> load(const std::string &name, const std::filesystem::path &filePath) override;
    };

}