#pragma once

#include <Clod/Graphic/ResourceManager.hpp>
#include <SFML/Audio.hpp>

namespace Clod
{
    class SoundBufferResourceManager : public ResourceManager<sf::SoundBuffer>
    {
        public:
            std::shared_ptr<sf::SoundBuffer> load(const std::string &name, const std::string &fileName) override;
    };
}
