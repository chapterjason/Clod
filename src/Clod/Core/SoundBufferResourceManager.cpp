#include <Clod/Core/SoundBufferResourceManager.hpp>

namespace Clod
{
    std::shared_ptr<sf::SoundBuffer> SoundBufferResourceManager::load(const std::string &name, const Path &path)
    {
        auto soundBuffer = std::make_shared<sf::SoundBuffer>();

        if (!soundBuffer->loadFromFile(std::filesystem::path(path)))
        {
            throw std::runtime_error("Failed to load sound buffer: " + name + " from file: " + path.string());
        }

        this->setMapping(name, path);
        this->set(name, soundBuffer);

        return soundBuffer;
    }

    std::shared_ptr<sf::SoundBuffer> SoundBufferResourceManager::load(const std::string &name, const void *data,
                                                                      const std::size_t size)
    {
        auto soundBuffer = std::make_shared<sf::SoundBuffer>();

        if (!soundBuffer->loadFromMemory(data, size))
        {
            throw std::runtime_error("Failed to load sound buffer: " + name + " from memory");
        }

        this->set(name, soundBuffer);

        return soundBuffer;
    }
}
