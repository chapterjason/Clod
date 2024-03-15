#pragma once

#include <Clod/Core/ResourceManager.hpp>
#include <Clod/Core/SoundBufferResourceManager.hpp>
#include <SFML/Audio.hpp>

namespace Clod
{
    class SoundResourceManager : public ResourceManager<sf::Sound>
    {
        protected:
            std::shared_ptr<SoundBufferResourceManager> soundBufferManager;

        public:
            explicit SoundResourceManager(const std::shared_ptr<SoundBufferResourceManager> &soundBufferManager);

            std::shared_ptr<sf::Sound> load(const std::string &name, const Path &path) override;

            std::shared_ptr<sf::Sound> load(const std::string &name, const void *data, std::size_t size) override;

            std::shared_ptr<sf::Sound> loadFromSoundBuffer(const std::string &name, const std::string &soundBufferName);

            std::shared_ptr<sf::Sound> loadFromSoundBuffer(const std::string &name,
                                                           const std::shared_ptr<sf::SoundBuffer> &soundBuffer);
    };
}
