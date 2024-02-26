#pragma once

#include <Clod/Core/ResourceManager.hpp>
#include <Clod/Core/TextureResourceManager.hpp>
#include <SFML/Graphics.hpp>


namespace Clod
{
    class SpriteResourceManager : public ResourceManager<sf::Sprite>
    {
        std::shared_ptr<TextureResourceManager> textureManager;

        public:
            explicit SpriteResourceManager(const std::shared_ptr<TextureResourceManager> &textureManager);

            std::shared_ptr<sf::Sprite> load(const std::string &name, const std::string &fileName) override;
    };
}
