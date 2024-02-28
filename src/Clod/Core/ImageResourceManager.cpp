#include <Clod/Core/ImageResourceManager.hpp>

namespace Clod
{
    std::shared_ptr<sf::Image> ImageResourceManager::load(const std::string &name, const std::filesystem::path &filePath)
    {
        auto image = std::make_shared<sf::Image>();

        if (!image->loadFromFile(filePath))
        {
            throw std::runtime_error("Failed to load image: " + name + " from file: " + filePath.string());
        }

        this->setMapping(name, filePath);
        this->set(name, image);

        return image;
    }

}
