#include <Clod/Core/ImageResourceManager.hpp>

namespace Clod
{
    std::shared_ptr<sf::Image> ImageResourceManager::load(const std::string &name, const Path &path)
    {
        auto image = std::make_shared<sf::Image>();

        if (!image->loadFromFile(std::filesystem::path(path)))
        {
            throw std::runtime_error("Failed to load image: " + name + " from file: " + path.string());
        }

        this->setMapping(name, path);
        this->set(name, image);

        return image;
    }

    std::shared_ptr<sf::Image> ImageResourceManager::load(const std::string &name, const void *data, const std::size_t size)
    {
        auto image = std::make_shared<sf::Image>();

        if (!image->loadFromMemory(data, size))
        {
            throw std::runtime_error("Failed to load image: " + name + " from memory");
        }

        this->set(name, image);

        return image;
    }
}
