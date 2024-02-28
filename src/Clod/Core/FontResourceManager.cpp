#include <Clod/Core/FontResourceManager.hpp>

namespace Clod
{
    std::shared_ptr<sf::Font> FontResourceManager::load(const std::string &name, const std::filesystem::path &filePath)
    {
        auto font = std::make_shared<sf::Font>();

        if (!font->loadFromFile(filePath))
        {
            throw std::runtime_error("Failed to load font: " + name + " from file: " + filePath.string());
        }

        this->setMapping(name, filePath);
        this->set(name, font);

        return font;
    }

}