#pragma once

#include <Clod/Graphic/ResourceManager.hpp>
#include <SFML/Graphics.hpp>

namespace Clod
{
    class ImageResourceManager : public ResourceManager<sf::Image>
    {
        public:
        std::shared_ptr<sf::Image> load(const std::string &name, const std::string &fileName) override;
    };

}