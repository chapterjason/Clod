#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Clod
{
    template<typename T>
    class ResourceManager
    {
        std::map<std::string, std::filesystem::path> fileMapping;
        std::map<std::string, std::shared_ptr<T>> resources;

        public:
            virtual ~ResourceManager();

            ResourceManager();

            void setMapping(const std::string &name, const std::filesystem::path &filePath);

            bool hasMapping(const std::string &name);

            std::filesystem::path getFileName(const std::string &name);

            bool has(const std::string &name);

            std::shared_ptr<T> get(const std::string &name);

            std::vector<std::string> getNames();

            void set(const std::string &name, std::shared_ptr<T> resource);

            void remove(const std::string &name);

            virtual std::shared_ptr<T> load(const std::string &name, const std::filesystem::path &filePath) = 0;
    };
}

#include <Clod/Core/ResourceManager.inl>
