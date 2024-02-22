#include <Clod/Graphic/FontResourceManager.hpp>

namespace Clod
{
    std::shared_ptr<sf::Font> FontResourceManager::load(const std::string &name, const std::string &fileName)
    {
        auto font = std::make_shared<sf::Font>();

        if (!font->loadFromFile(fileName))
        {
            throw std::runtime_error("Failed to load font: " + name + " from file: " + fileName);
        }

        this->set(name, font);

        return font;
    }

}