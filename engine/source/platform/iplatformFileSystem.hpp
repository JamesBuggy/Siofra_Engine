#pragma once

#include <vector>
#include <map>
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
         * @brief Read data from a config file
         *
         * @param filePath Path to the config file
         * @returns Config file entries as key value pairs 
         */
        virtual std::map<std::string, std::string> readConfigFile(const std::string& filePath) const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IPlatformFileSystem() = default;
    };
}
