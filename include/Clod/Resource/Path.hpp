#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include "PathType.hpp"

namespace Clod
{
    class Path
    {
        protected:
            PathType type = Directory;
            std::vector<std::string> items = {};

            static std::string normalize(const std::string &path);

            static std::vector<std::string> split(const std::string &path);

        public:
            static Path current();

            static Path root();

            Path();

            explicit Path(const std::filesystem::path &path);

            Path(const std::string &path, const PathType &type);

            Path(const std::vector<std::string> &items, const PathType &type);

            Path(const char *path, const PathType &type);

            bool isDirectory() const;

            bool isFile() const;

            Path join(const Path &path) const;

            Path file(const Path &path) const;

            Path file(const std::string &filename) const;

            Path directory(const std::string &directoryName) const;

            Path join(const std::string &path, const PathType &type) const;

            Path join(const char *path, const PathType &type) const;

            bool isRoot() const;

            [[nodiscard]] Path trim() const;

            [[nodiscard]] std::string getBasename() const;

            [[nodiscard]] std::string getFilename() const;

            [[nodiscard]] std::string getDirname() const;

            [[nodiscard]] std::string getName() const;

            [[nodiscard]] std::string getExtension() const;

            std::string string() const;

            [[nodiscard]] Path getDirectory() const;

            [[nodiscard]] PathType getType() const;

            // COMPARE
            bool operator==(const Path &path) const;

            // CAST
            operator std::filesystem::path() const;

            operator std::string() const;
    };
}
