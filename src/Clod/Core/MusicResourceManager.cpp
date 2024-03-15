#include <Clod/Core/MusicResourceManager.hpp>

namespace Clod
{
    std::shared_ptr<sf::Music> MusicResourceManager::load(const std::string &name, const Path &path)
    {
        auto music = std::make_shared<sf::Music>();

        if (!music->openFromFile(std::filesystem::path(path)))
        {
            throw std::runtime_error("Failed to load music: " + name + " from file: " + path.string());
        }

        this->setMapping(name, path);
        this->set(name, music);

        return music;
    }

    std::shared_ptr<sf::Music> MusicResourceManager::load(const std::string &name, const void *data, const std::size_t size)
    {
        auto music = std::make_shared<sf::Music>();

        if (!music->openFromMemory(data, size))
        {
            throw std::runtime_error("Failed to load music: " + name + " from memory");
        }

        this->set(name, music);

        return music;
    }

    std::shared_ptr<sf::Music> MusicResourceManager::load(const std::string &name, const std::string &filePath)
    {
        return ResourceManager<sf::Music>::load(name, filePath);
    }
}
