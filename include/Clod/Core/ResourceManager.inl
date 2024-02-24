#pragma once

#include <stdexcept>

#include <Clod/Core/ResourceManager.hpp>

namespace Clod
{
    template<typename T>
    ResourceManager<T>::~ResourceManager() = default;

    template<typename T>
    ResourceManager<T>::ResourceManager()
    {
        this->resources = std::map<std::string, std::shared_ptr<T> >();
        this->categories = std::map<std::string, std::vector<std::string> >();
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
            throw std::runtime_error("Resource not found: " + name);
        }

        return resources[name];
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
    void ResourceManager<T>::clear(const std::string &category)
    {
        if (category.empty())
        {
            resources.clear();
            categories.clear();
        }
        else
        {
            for (auto &name: categories[category])
            {
                resources.erase(name);
            }

            categories.erase(category);
        }
    }
}
