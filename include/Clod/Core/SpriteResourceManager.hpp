#pragma once

#include <Clod/Core/ResourceManager.hpp>
#include <Clod/Core/TextureResourceManager.hpp>
#include <SFML/Graphics.hpp>

namespace Clod
{
    class SpriteResourceManager : public ResourceManager<sf::Sprite>
    {
        std::shared_ptr<TextureResourceManager> textureManager;

        public:
            explicit SpriteResourceManager(const std::shared_ptr<TextureResourceManager> &textureManager);

            std::shared_ptr<sf::Sprite> load(const std::string &name, const Path &path) override;

            std::shared_ptr<sf::Sprite> load(const std::string &name, const void *data, std::size_t size) override;

            std::shared_ptr<sf::Sprite> loadFromImage(const std::string &name, const std::string &imageName);

            std::shared_ptr<sf::Sprite> loadFromImage(const std::string &name, const std::shared_ptr<sf::Image> &image);

            std::shared_ptr<sf::Sprite> loadFromTexture(const std::string &name, const std::string &textureName);

            std::shared_ptr<sf::Sprite> loadFromTexture(const std::string &name, const std::shared_ptr<sf::Texture> &texture);

            std::shared_ptr<sf::Sprite> load(const std::string &name, const std::string &filePath) override;
    };
}
