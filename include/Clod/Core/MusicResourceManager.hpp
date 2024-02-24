#pragma once

#include <Clod/Core/ResourceManager.hpp>
#include <SFML/Audio.hpp>

// @todo: No fitting module name for music?

namespace Clod
{
    class MusicResourceManager : public ResourceManager<sf::Music>
    {
        public:
            std::shared_ptr<sf::Music> load(const std::string &name, const std::string &fileName) override;
    };
}