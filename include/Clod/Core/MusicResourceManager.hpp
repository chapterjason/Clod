#pragma once

#include <Clod/Core/ResourceManager.hpp>
#include <SFML/Audio.hpp>

namespace Clod
{
    class MusicResourceManager : public ResourceManager<sf::Music>
    {
        public:
            std::shared_ptr<sf::Music> load(const std::string &name, const std::filesystem::path &filePath) override;
    };
}