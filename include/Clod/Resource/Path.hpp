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

            [[nodiscard]] bool isDirectory() const;

            [[nodiscard]] bool isFile() const;

            [[nodiscard]] Path join(const Path &path) const;

            [[nodiscard]] Path file(const Path &path) const;

            [[nodiscard]] Path file(const std::string &filename) const;

            [[nodiscard]] Path directory(const std::string &directoryName) const;

            [[nodiscard]] Path join(const std::string &path, const PathType &type) const;

            [[nodiscard]] Path join(const char *path, const PathType &type) const;

            [[nodiscard]] bool isRoot() const;

            [[nodiscard]] Path trim() const;

            [[nodiscard]] std::string getBasename() const;

            [[nodiscard]] std::string getFilename() const;

            [[nodiscard]] std::string getDirname() const;

            [[nodiscard]] std::string getName() const;

            [[nodiscard]] std::string getExtension() const;

            [[nodiscard]] std::string string() const;

            [[nodiscard]] Path getDirectory() const;

            [[nodiscard]] PathType getType() const;

            // COMPARE
            bool operator==(const Path &path) const;

            bool operator!=(const Path &path) const;

            // SORT COMPARE
            bool operator<(const Path &path) const;

            bool operator>(const Path &path) const;

            bool operator<=(const Path &path) const;

            bool operator>=(const Path &path) const;

            // CAST
            explicit operator std::filesystem::path() const;

            explicit operator std::string() const;
    };
}
