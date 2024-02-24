#pragma once

#include <Clod/Core/ResourceManager.hpp>
#include <SFML/Graphics.hpp>

namespace Clod
{
    class FontResourceManager : public ResourceManager<sf::Font>
    {
        public:
            std::shared_ptr<sf::Font> load(const std::string &name, const std::string &fileName) override;
    };
}
