#pragma once

#include <vector>
#include <string>

namespace siofraEngine::platform
{
    /**
     * @brief Platform file system interface
     */
    class IPlatformFileSystem
    {
    public:
        /**
         * @brief Read all bytes from a file
         * 
         * @param filePath Path to the file
         * @returns File content bytes
         */
        virtual std::vector<char> readFile(const std::string & filePath) const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IPlatformFileSystem() = default;
    };
}
