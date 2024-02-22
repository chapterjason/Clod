#include <Clod/Graphic/MusicResourceManager.hpp>

namespace Clod
{
    std::shared_ptr<sf::Music> MusicResourceManager::load(const std::string &name, const std::string &fileName)
    {
        auto music = std::make_shared<sf::Music>();

        if (!music->openFromFile(fileName))
        {
            throw std::runtime_error("Failed to load music: " + name + " from file: " + fileName);
        }

        this->set(name, music);

        return music;
    }
}
