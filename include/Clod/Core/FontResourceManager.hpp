#pragma once

#include <Clod/Core/ResourceManager.hpp>
#include <SFML/Graphics.hpp>

namespace Clod
{
    class FontResourceManager : public ResourceManager<sf::Font>
    {
        public:
            std::shared_ptr<sf::Font> load(const std::string &name, const Path &path) override;

            std::shared_ptr<sf::Font> load(const std::string &name, const void *data, std::size_t size) override;

            std::shared_ptr<sf::Font> load(const std::string &name, const std::string &filePath) override;
    };
}
