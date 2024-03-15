#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Clod/Resource/Path.hpp"

namespace Clod
{
    template<typename T>
    class ResourceManager
    {
        std::map<std::string, Path> fileMapping;
        std::map<std::string, std::shared_ptr<T>> resources;

        public:
            virtual ~ResourceManager();

            ResourceManager();

            /// Mapping
            void setMapping(const std::string &name, const Path &path);

            void setMapping(const std::string &name, const std::string &filePath);

            [[nodiscard]] bool hasMapping(const std::string &name) const;

            Path getPath(const std::string &name);

            std::vector<std::string> getNames();

            /// Accessors
            bool has(const std::string &name);

            std::shared_ptr<T> get(const std::string &name);

            void set(const std::string &name, std::shared_ptr<T> resource);

            void remove(const std::string &name);

            virtual std::shared_ptr<T> load(const std::string &name, const Path &path) = 0;

            virtual std::shared_ptr<T> load(const std::string &name, const void* data, std::size_t size) = 0;
    };
}

#include <Clod/Core/ResourceManager.inl>
