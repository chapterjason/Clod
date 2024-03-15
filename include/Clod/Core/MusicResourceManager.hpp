#pragma once

#include <Clod/Core/ResourceManager.hpp>
#include <SFML/Audio.hpp>

namespace Clod
{
    class MusicResourceManager : public ResourceManager<sf::Music>
    {
        public:
            std::shared_ptr<sf::Music> load(const std::string &name, const Path &path) override;

            std::shared_ptr<sf::Music> load(const std::string &name, const void *data, std::size_t size) override;
    };
}