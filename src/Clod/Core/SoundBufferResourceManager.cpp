#include <Clod/Core/SoundBufferResourceManager.hpp>

namespace Clod
{
    std::shared_ptr<sf::SoundBuffer> SoundBufferResourceManager::load(const std::string &name, const std::filesystem::path &filePath)
    {
        auto soundBuffer = std::make_shared<sf::SoundBuffer>();

        if (!soundBuffer->loadFromFile(filePath))
        {
            throw std::runtime_error("Failed to load sound buffer: " + name + " from file: " + filePath.string());
        }

        this->setMapping(name, filePath);
        this->set(name, soundBuffer);

        return soundBuffer;
    }
}