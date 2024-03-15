#include <Clod/Core/FontResourceManager.hpp>

namespace Clod
{
    std::shared_ptr<sf::Font> FontResourceManager::load(const std::string &name, const Path &path)
    {
        auto font = std::make_shared<sf::Font>();

        if (!font->loadFromFile(std::filesystem::path(path)))
        {
            throw std::runtime_error("Failed to load font: " + name + " from file: " + path.string());
        }

        this->setMapping(name, path);
        this->set(name, font);

        return font;
    }

    std::shared_ptr<sf::Font> FontResourceManager::load(const std::string &name, const void *data, const std::size_t size)
    {
        auto font = std::make_shared<sf::Font>();

        if (!font->loadFromMemory(data, size))
        {
            throw std::runtime_error("Failed to load font: " + name + " from memory");
        }

        this->set(name, font);

        return font;
    }

    std::shared_ptr<sf::Font> FontResourceManager::load(const std::string &name, const std::string &filePath)
    {
        return ResourceManager<sf::Font>::load(name, filePath);
    }
}
