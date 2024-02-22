
#include <Clod/Graphic/ImageResourceManager.hpp>

namespace Clod
{
    std::shared_ptr<sf::Image> ImageResourceManager::load(const std::string &name, const std::string &fileName)
    {
        auto image = std::make_shared<sf::Image>();

        if (!image->loadFromFile(fileName))
        {
            throw std::runtime_error("Failed to load image: " + name + " from file: " + fileName);
        }

        this->set(name, image);

        return image;
    }

}
