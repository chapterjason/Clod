
#include <Clod/Graphic/TextureResourceManager.hpp>

namespace Clod
{
    std::shared_ptr<sf::Texture> TextureResourceManager::load(const std::string &name, const std::string &fileName)
    {
        auto texture = std::make_shared<sf::Texture>();

        if (!texture->loadFromFile(fileName))
        {
            throw std::runtime_error("Failed to load texture: " + name + " from file: " + fileName);
        }

        this->set(name, texture);

        return texture;
    }

    std::shared_ptr<sf::Texture> TextureResourceManager::loadFromImage(const std::string &name,
                                                                       const std::shared_ptr<sf::Image> &image)
    {
        if (this->has(name))
        {
            throw std::runtime_error("Texture: " + name + " already exists");
        }

        auto texture = std::make_shared<sf::Texture>();

        if(!texture->loadFromImage(*image))
        {
            throw std::runtime_error("Failed to load texture: " + name + " from image");
        }

        this->set(name, texture);

        return texture;
    }

    std::shared_ptr<sf::Texture> TextureResourceManager::subTexture(const std::string &name, const std::string &reference,
                                                                    const sf::IntRect &crop)
    {
        if (this->has(name))
        {
            throw std::runtime_error("Texture: " + name + " already exists");
        }

        const auto texture = this->get(reference);

        auto subTexture = std::make_shared<sf::Texture>();

         if(!subTexture->loadFromImage(texture->copyToImage(), crop))
         {
             throw std::runtime_error("Failed to create subtexture: " + name);
         }

        this->set(name, subTexture);

        return subTexture;
    }
}
