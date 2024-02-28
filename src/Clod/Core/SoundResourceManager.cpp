#include <Clod/Core/SoundResourceManager.hpp>

namespace Clod
{
    SoundResourceManager::SoundResourceManager(const std::shared_ptr<SoundBufferResourceManager> &soundBufferManager)
        : soundBufferManager(soundBufferManager) {}

    std::shared_ptr<sf::Sound> SoundResourceManager::load(const std::string &name, const std::filesystem::path &filePath)
    {
        if (!soundBufferManager->has(name))
        {
            soundBufferManager->load(name, filePath);
        }

        const auto soundBuffer = soundBufferManager->get(name);

        auto sound = std::make_shared<sf::Sound>(*soundBuffer);

        this->setMapping(name, filePath);
        this->set(name, sound);

        return sound;
    }
}
