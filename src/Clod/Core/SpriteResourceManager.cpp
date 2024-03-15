#include <Clod/Core/SpriteResourceManager.hpp>
#include <Clod/Core/TextureResourceManager.hpp>

namespace Clod
{
    SpriteResourceManager::SpriteResourceManager(const std::shared_ptr<TextureResourceManager> &textureManager)
        : textureManager(textureManager) {}

    std::shared_ptr<sf::Sprite> SpriteResourceManager::load(const std::string &name,
                                                            const Path &path)
    {
        const auto textureName = name + "_sprite_texture";

        const auto texture = !textureManager->has(textureName)
                                 ? textureManager->load(textureName, path)
                                 : textureManager->get(textureName);

        auto sprite = std::make_shared<sf::Sprite>(*texture);

        this->setMapping(name, path);
        this->set(name, sprite);

        return sprite;
    }

    std::shared_ptr<sf::Sprite> SpriteResourceManager::load(const std::string &name, const void *data, const std::size_t size)
    {
        const auto textureName = name + "_sprite_texture";

        const auto texture = !textureManager->has(textureName)
                                 ? textureManager->load(textureName, data, size)
                                 : textureManager->get(textureName);

        auto sprite = std::make_shared<sf::Sprite>(*texture);

        this->set(name, sprite);

        return sprite;
    }

    std::shared_ptr<sf::Sprite> SpriteResourceManager::loadFromImage(const std::string &name,
        const std::string &imageName)
    {
        const auto textureName = name + "_sprite_texture";

        const auto texture = textureManager->loadFromImage(textureName, imageName);

        auto sprite = std::make_shared<sf::Sprite>(*texture);

        this->set(name, sprite);

        return sprite;
    }

    std::shared_ptr<sf::Sprite> SpriteResourceManager::loadFromImage(const std::string &name,
        const std::shared_ptr<sf::Image> &image)
    {
        const auto textureName = name + "_sprite_texture";

        const auto texture = textureManager->loadFromImage(textureName, image);

        auto sprite = std::make_shared<sf::Sprite>(*texture);

        this->set(name, sprite);

        return sprite;
    }

    std::shared_ptr<sf::Sprite> SpriteResourceManager::loadFromTexture(const std::string &name,
        const std::string &textureName)
    {
        const auto texture = textureManager->get(textureName);

        auto sprite = std::make_shared<sf::Sprite>(*texture);

        this->set(name, sprite);

        return sprite;
    }

    std::shared_ptr<sf::Sprite> SpriteResourceManager::loadFromTexture(const std::string &name,
        const std::shared_ptr<sf::Texture> &texture)
    {
        const auto textureName = name + "_sprite_texture";

        if (!textureManager->has(textureName))
        {
            textureManager->set(textureName, texture);
        }

        // @todo Use the texture manager to load the texture or use the passed texture?

        const auto sprite = std::make_shared<sf::Sprite>(*texture);

        this->set(name, sprite);

        return sprite;
    }

    std::shared_ptr<sf::Sprite> SpriteResourceManager::load(const std::string &name, const std::string &filePath)
    {
        return ResourceManager<sf::Sprite>::load(name, filePath);
    }
}
