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

            std::shared_ptr<sf::Sound> load(const std::string &name, const std::string &fileName) override;
    };
}