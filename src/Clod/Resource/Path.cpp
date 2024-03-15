#include <Clod/Resource/Path.hpp>
#include <algorithm>

namespace Clod
{
    std::string Path::normalize(const std::string &path)
    {
        std::string normalized = path;

        std::ranges::transform(normalized, normalized.begin(), [](unsigned char c)
        {
            return c == '\\' ? '/' : c;
        });

        return normalized;
    }

    std::vector<std::string> Path::split(const std::string &path)
    {
        std::vector<std::string> items;
        std::string item;

        for (const auto &character: normalize(path))
        {
            if (character == '/')
            {
                items.push_back(item);
                item.clear();
            }
            else
            {
                item += character;
            }
        }

        // Add the last item or the only item (root case), basically Path("") == Path("/")
        if (!item.empty() || items.empty())
        {
            items.push_back(item);
        }

        return items;
    }

    Path Path::current()
    {
        return Path(std::filesystem::current_path());
    }

    Path Path::root()
    {
        return {"/", Directory};
    }

    Path::Path() = default;

    Path::Path(const std::filesystem::path &path)
        : items(split(path.string()))
    {
        if (std::filesystem::is_directory(path))
        {
            this->type = Directory;
        }
        else if (std::filesystem::is_regular_file(path))
        {
            this->type = File;
        }
        else
        {
            throw std::invalid_argument("Path is neither a directory nor a file");
        }
    }

    Path::Path(const std::string &path, const PathType &type)
        : type(type), items(split(path)) {}

    Path::Path(const std::vector<std::string> &items, const PathType &type)
        : type(type), items(items) {}

    Path::Path(const char *path, const PathType &type)
        : type(type), items(split(path)) {}

    bool Path::isDirectory() const
    {
        return this->type == Directory;
    }

    bool Path::isFile() const
    {
        return this->type == File;
    }

    Path Path::join(const Path &path) const
    {
        std::vector<std::string> joinedItems = items;
        joinedItems.insert(joinedItems.end(), path.items.begin(), path.items.end());

        if (this->isDirectory() && path.isDirectory())
        {
            return Path{joinedItems, Directory};
        }

        if (this->isFile() && path.isFile())
        {
            return Path{joinedItems, File};
        }

        if (this->isDirectory() && path.isFile())
        {
            return Path{joinedItems, File};
        }

        throw std::invalid_argument("Cannot join a file with a directory");
    }

    Path Path::file(const Path &path) const
    {
        if (this->isDirectory() && path.isFile())
        {
            std::vector<std::string> joinedItems = items;
            joinedItems.push_back(path.getBasename());

            return Path{joinedItems, File};
        }
        else
        {
            throw std::invalid_argument("Can only join a directory with a file");
        }
    }

    Path Path::file(const std::string &filename) const
    {
        if (this->isDirectory())
        {
            const auto parts = Path::split(filename);

            auto joinedItems = this->items;

            joinedItems.insert(joinedItems.end(), parts.begin(), parts.end());

            return Path{joinedItems, File};
        }
        else
        {
            const auto directory = this->getDirectory();

            return directory.file(filename);
        }
    }

    Path Path::directory(const std::string &directoryName) const
    {
        if (this->isDirectory())
        {
            const auto parts = Path::split(directoryName);

            auto joinedItems = this->items;

            joinedItems.insert(joinedItems.end(), parts.begin(), parts.end());

            return Path{joinedItems, Directory};
        }
        else
        {
            const auto directory = this->getDirectory();

            return directory.directory(directoryName);
        }
    }

    Path Path::join(const std::string &path, const PathType &type) const
    {
        return join(Path{path, type});
    }

    Path Path::join(const char *path, const PathType &type) const
    {
        return join(Path{path, type});
    }

    bool Path::isRoot() const
    {
        return this->items.empty() || (this->items.size() == 1 && this->items[0].empty());
    }

    Path Path::trim() const
    {
        // Remove first item if it's empty
        auto trimmedItems = items;

        if (!trimmedItems.empty() && trimmedItems[0].empty())
        {
            trimmedItems.erase(trimmedItems.begin());
        }

        return Path{trimmedItems, type};
    }

    std::string Path::getBasename() const
    {
        return this->items.back();
    }

    std::string Path::getFilename() const
    {
        if (this->isFile())
        {
            const auto &basename = this->getBasename();
            const auto &extension = this->getExtension();

            return basename.substr(0, basename.size() - extension.size());
        }

        throw std::invalid_argument("Path is not a file");
    }

    std::string Path::getDirname() const
    {
        if (this->isDirectory())
        {
            return this->getBasename();
        }

        throw std::invalid_argument("Path is not a directory");
    }

    std::string Path::getName() const
    {
        if (this->isDirectory())
        {
            return this->getDirname();
        }
        else if (this->isFile())
        {
            return this->getFilename();
        }

        return this->getBasename();
    }

    std::string Path::getExtension() const
    {
        if (this->isFile())
        {
            const auto &basename = this->getBasename();
            const auto dotIndex = basename.find_last_of('.');

            return dotIndex != std::string::npos ? basename.substr(dotIndex) : "";
        }

        throw std::invalid_argument("Path is not a file");
    }

    std::string Path::string() const
    {
        if (this->isRoot())
        {
            return "/";
        }

        std::string str;

        for (const auto &item: items)
        {
            if (&item == &items.back())
            {
                str += item;
            }
            else
            {
                str += item + "/";
            }
        }

        return str;
    }

    Path Path::getDirectory() const
    {
        auto directoryItems = items;

        if (!directoryItems.empty())
        {
            directoryItems.pop_back();
        }

        return Path{directoryItems, Directory};
    }

    PathType Path::getType() const
    {
        return this->type;
    }

    bool Path::operator==(const Path &path) const
    {
        return this->items == path.items;
    }

    bool Path::operator!=(const Path &path) const
    {
        return this->items != path.items;
    }

    bool Path::operator<(const Path &path) const
    {
        return this->string() < path.string();
    }

    bool Path::operator>(const Path &path) const
    {
        return this->string() > path.string();
    }

    bool Path::operator<=(const Path &path) const
    {
        return this->string() <= path.string();
    }

    bool Path::operator>=(const Path &path) const
    {
        return this->string() >= path.string();
    }

    Path::operator std::filesystem::path() const
    {
        return {this->string()};
    }

    Path::operator std::string() const
    {
        return this->string();
    }
}
