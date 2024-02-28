#include <Clod/Core/MusicResourceManager.hpp>

namespace Clod
{
    std::shared_ptr<sf::Music> MusicResourceManager::load(const std::string &name, const std::filesystem::path &filePath)
    {
        auto music = std::make_shared<sf::Music>();

        if (!music->openFromFile(filePath))
        {
            throw std::runtime_error("Failed to load music: " + name + " from file: " + filePath.string());
        }

        this->setMapping(name, filePath);
        this->set(name, music);

        return music;
    }
}
