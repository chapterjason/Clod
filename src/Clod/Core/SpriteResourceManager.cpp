#include <Clod/Core/SpriteResourceManager.hpp>

#include "Clod/Core/TextureResourceManager.hpp"

namespace Clod
{
    SpriteResourceManager::SpriteResourceManager(const std::shared_ptr<TextureResourceManager> &textureManager)
        : textureManager(textureManager) {}

    std::shared_ptr<sf::Sprite> SpriteResourceManager::load(const std::string &name, const std::string &fileName)
    {
        const auto textureName = name + "_sprite_texture";

        const auto texture = !textureManager->has(textureName)
                                 ? textureManager->load(textureName, fileName)
                                 : textureManager->get(textureName);

        auto sprite = std::make_shared<sf::Sprite>(*texture);

        this->set(name, sprite);

        return sprite;
    }
}