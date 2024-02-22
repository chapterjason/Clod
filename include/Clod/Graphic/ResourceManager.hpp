#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Clod
{
    template<typename T>
    class ResourceManager
    {
        std::map<std::string, std::shared_ptr<T> > resources;
        std::map<std::string, std::vector<std::string> > categories;

        public:
            virtual ~ResourceManager();

            ResourceManager();

            bool has(const std::string &name);

            std::shared_ptr<T> get(const std::string &name);

            void set(const std::string &name, std::shared_ptr<T> resource);

            void clear(const std::string &category = "");

            virtual std::shared_ptr<T> load(const std::string &name, const std::string &fileName) = 0;
    };
}

#include <Clod/Graphic/ResourceManager.inl>
