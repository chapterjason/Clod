#pragma once

#include <algorithm>
#include <stdexcept>

#include <Clod/Core/ResourceManager.hpp>

namespace Clod
{
    template<typename T>
    ResourceManager<T>::~ResourceManager() = default;

    template<typename T>
    ResourceManager<T>::ResourceManager()
    {
        this->fileNames = std::map<std::string, std::string>();
        this->resources = std::map<std::string, std::shared_ptr<T> >();
    }

    template<typename T>
    void ResourceManager<T>::addMapping(const std::string &name, const std::string &fileName)
    {
        this->fileNames[name] = fileName;
    }

    template<typename T>
    bool ResourceManager<T>::hasMapping(const std::string &name)
    {
        return fileNames.find(name) != fileNames.end();
    }

    template<typename T>
    std::string ResourceManager<T>::getMapping(const std::string &name)
    {
        return fileNames[name];
    }

    template<typename T>
    bool ResourceManager<T>::has(const std::string &name)
    {
        return resources.find(name) != resources.end();
    }

    template<typename T>
    std::shared_ptr<T> ResourceManager<T>::get(const std::string &name)
    {
        if (!this->has(name))
        {
            if (this->hasMapping(name))
            {
                const auto fileName = this->getMapping(name);

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

        for (const auto &pair : fileNames)
        {
            names.push_back(pair.first);
        }

        for (const auto &pair : resources)
        {
            names.push_back(pair.first);
        }

        std::sort(names.begin(), names.end());

        names.erase(std::unique(names.begin(), names.end()), names.end());

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
