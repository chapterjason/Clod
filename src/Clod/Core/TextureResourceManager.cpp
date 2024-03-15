#include <Clod/Core/TextureResourceManager.hpp>

namespace Clod
{
    TextureResourceManager::TextureResourceManager(const std::shared_ptr<ImageResourceManager> &imageManager): imageManager(imageManager)
    {}

    std::shared_ptr<sf::Texture> TextureResourceManager::load(const std::string &name, const Path &path)
    {
        auto texture = std::make_shared<sf::Texture>();

        if (!texture->loadFromFile(std::filesystem::path(path)))
        {
            throw std::runtime_error("Failed to load texture: " + name + " from file: " + path.string());
        }

        this->setMapping(name, path);
        this->set(name, texture);

        return texture;
    }

    std::shared_ptr<sf::Texture> TextureResourceManager::load(const std::string &name, const void *data, const std::size_t size)
    {
        auto texture = std::make_shared<sf::Texture>();

        if (!texture->loadFromMemory(data, size))
        {
            throw std::runtime_error("Failed to load texture: " + name + " from memory");
        }

        this->set(name, texture);

        return texture;
    }

    std::shared_ptr<sf::Texture> TextureResourceManager::loadFromImage(const std::string &name,
        const std::string &imageName)
    {
        const auto soundBuffer = imageManager->get(imageName);

        return this->loadFromImage(name, soundBuffer);
    }

    std::shared_ptr<sf::Texture> TextureResourceManager::loadFromImage(const std::string &name,
                                                                       const std::shared_ptr<sf::Image> &image)
    {
        const auto imageName = name + "_texture_image";

        if(!this->imageManager->has(imageName))
        {
            this->imageManager->set(imageName, image);
        }

        // @todo Getting the image from the imageManager or using the one passed as argument?

        const auto texture = std::make_shared<sf::Texture>();

        if (!texture->loadFromImage(*image))
        {
            throw std::runtime_error("Failed to load texture: " + name + " from image: " + imageName);
        }

        this->set(name, texture);

        return texture;
    }

    std::shared_ptr<sf::Texture> TextureResourceManager::subTexture(const std::string &name,
                                                                    const std::string &reference,
                                                                    const sf::IntRect &crop
    )
    {
        if (this->has(name))
        {
            throw std::runtime_error("Texture: " + name + " already exists");
        }

        const auto texture = this->get(reference);

        auto subTexture = std::make_shared<sf::Texture>();

        if (!subTexture->loadFromImage(texture->copyToImage(), crop))
        {
            throw std::runtime_error("Failed to create subtexture: " + name);
        }

        this->set(name, subTexture);

        return subTexture;
    }

    std::shared_ptr<sf::Texture> TextureResourceManager::load(const std::string &name, const std::string &filePath)
    {
        return ResourceManager<sf::Texture>::load(name, filePath);
    }
}
