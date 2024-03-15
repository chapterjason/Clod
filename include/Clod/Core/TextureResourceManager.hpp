#pragma once

#include <Clod/Core/ResourceManager.hpp>
#include <SFML/Graphics.hpp>

#include "ImageResourceManager.hpp"

namespace Clod
{
    class TextureResourceManager : public ResourceManager<sf::Texture>
    {
        protected:
            std::shared_ptr<ImageResourceManager> imageManager;

        public:
            explicit TextureResourceManager(const std::shared_ptr<ImageResourceManager> &imageManager);

            std::shared_ptr<sf::Texture> load(const std::string &name, const Path &path) override;

            std::shared_ptr<sf::Texture> load(const std::string &name, const void *data, std::size_t size) override;

            std::shared_ptr<sf::Texture> loadFromImage(const std::string &name, const std::string &imageName);

            std::shared_ptr<sf::Texture> loadFromImage(const std::string &name, const std::shared_ptr<sf::Image> &image);

            std::shared_ptr<sf::Texture> subTexture(const std::string &name,
                                                    const std::string &reference,
                                                    const sf::IntRect &crop);

            std::shared_ptr<sf::Texture> load(const std::string &name, const std::string &filePath) override;
    };
}
