#include <Clod/Core/SoundResourceManager.hpp>

namespace Clod
{
    SoundResourceManager::SoundResourceManager(const std::shared_ptr<SoundBufferResourceManager> &soundBufferManager)
        : soundBufferManager(soundBufferManager) {}

    std::shared_ptr<sf::Sound> SoundResourceManager::load(const std::string &name, const Path &path)
    {
        const auto soundBufferName = name + "_sound_sound_buffer";

        const auto soundBuffer = !soundBufferManager->has(soundBufferName)
                                     ? soundBufferManager->load(soundBufferName, path)
                                     : soundBufferManager->get(soundBufferName);

        auto sound = std::make_shared<sf::Sound>(*soundBuffer);

        this->setMapping(name, path);
        this->set(name, sound);

        return sound;
    }

    std::shared_ptr<sf::Sound> SoundResourceManager::load(const std::string &name, const void *data,
                                                          const std::size_t size)
    {
        const auto soundBufferName = name + "_sound_sound_buffer";

        const auto soundBuffer = !soundBufferManager->has(soundBufferName)
                                     ? soundBufferManager->load(soundBufferName, data, size)
                                     : soundBufferManager->get(soundBufferName);

        auto sound = std::make_shared<sf::Sound>(*soundBuffer);

        this->set(name, sound);

        return sound;
    }

    std::shared_ptr<sf::Sound> SoundResourceManager::loadFromSoundBuffer(const std::string &name, const std::string &soundBufferName) {
        const auto soundBuffer = soundBufferManager->get(soundBufferName);

        return this->loadFromSoundBuffer(name, soundBuffer);
    }

    std::shared_ptr<sf::Sound> SoundResourceManager::loadFromSoundBuffer(const std::string &name,
        const std::shared_ptr<sf::SoundBuffer> &soundBuffer)
    {
        const auto soundBufferName = name + "_sound_sound_buffer";

        if(!this->soundBufferManager->has(soundBufferName))
        {
            this->soundBufferManager->set(soundBufferName, soundBuffer);
        }

        // @todo Getting the SoundBuffer from the SoundManager or using the one passed as argument?

        const auto sound = std::make_shared<sf::Sound>(*soundBuffer);

        this->set(name, sound);

        return sound;
    }
}
