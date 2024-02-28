#pragma once

#include <Clod/Core/ResourceManager.hpp>
#include <SFML/Graphics.hpp>

namespace Clod
{
    class TextureResourceManager : public ResourceManager<sf::Texture>
    {
        public:
            std::shared_ptr<sf::Texture> load(const std::string &name, const std::filesystem::path &filePath) override;

            std::shared_ptr<sf::Texture> loadFromImage(const std::string &name,
                                                       const std::shared_ptr<sf::Image> &image);

            std::shared_ptr<sf::Texture> subTexture(const std::string &name,
                                                    const std::string &reference,
                                                    const sf::IntRect &crop);
    };
}
