#pragma once

#include <algorithm>
#include <stdexcept>
#include <ranges>

#include <Clod/Core/ResourceManager.hpp>

namespace Clod
{
    template<typename T>
    ResourceManager<T>::~ResourceManager() = default;

    template<typename T>
    ResourceManager<T>::ResourceManager()
    {
        this->fileMapping = std::map<std::string, std::filesystem::path>();
        this->resources = std::map<std::string, std::shared_ptr<T>>();
    }

    template<typename T>
    void ResourceManager<T>::setMapping(const std::string &name, const std::filesystem::path &filePath)
    {
        this->fileMapping[name] = filePath;
    }

    template<typename T>
    bool ResourceManager<T>::hasMapping(const std::string &name) const
    {
        return fileMapping.contains(name);
    }

    template<typename T>
    std::filesystem::path ResourceManager<T>::getFileName(const std::string &name)
    {
        return fileMapping[name];
    }

    template<typename T>
    bool ResourceManager<T>::has(const std::string &name)
    {
        return this->resources.contains(name);
    }

    template<typename T>
    std::shared_ptr<T> ResourceManager<T>::get(const std::string &name)
    {
        if (!this->has(name))
        {
            if (this->hasMapping(name))
            {
                const auto fileName = this->getFileName(name);

                return this->load(name, fileName);
            }

            throw std::runtime_error("Resource not found: " + name);
        }

        return resources[name];
    }

    template<typename T>
    std::vector<std::string> ResourceManager<T>::getNames()
    {
        std::vector<std::string> names;

        for (const auto &key: std::views::keys(fileMapping))
        {
            names.push_back(key);
        }

        for (const auto &pair: resources)
        {
            names.push_back(pair.first);
        }

        std::ranges::sort(names);

        names.erase(std::ranges::unique(names).begin(), names.end());

        return names;
    }

    template<typename T>
    void ResourceManager<T>::set(const std::string &name, std::shared_ptr<T> resource)
    {
        if (this->has(name))
        {
            throw std::runtime_error("Resource already exists: " + name);
        }

        resources[name] = resource;
    }

    template<typename T>
    void ResourceManager<T>::remove(const std::string &name)
    {
        this->resources.erase(name);
    }
}
