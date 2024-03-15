#pragma once

#include <Clod/Core/ResourceManager.hpp>
#include <SFML/Audio.hpp>

namespace Clod
{
    class SoundBufferResourceManager : public ResourceManager<sf::SoundBuffer>
    {
        public:
            std::shared_ptr<sf::SoundBuffer> load(const std::string &name, const Path &path) override;

            std::shared_ptr<sf::SoundBuffer> load(const std::string &name, const void *data, std::size_t size) override;
    };
}
