#include <Clod/Core/SoundBufferResourceManager.hpp>

namespace Clod
{
    std::shared_ptr<sf::SoundBuffer> SoundBufferResourceManager::load(const std::string &name, const std::string &fileName)
    {
        auto soundBuffer = std::make_shared<sf::SoundBuffer>();

        if (!soundBuffer->loadFromFile(fileName))
        {
            throw std::runtime_error("Failed to load sound buffer: " + name + " from file: " + fileName);
        }

        this->set(name, soundBuffer);

        return soundBuffer;
    }
}