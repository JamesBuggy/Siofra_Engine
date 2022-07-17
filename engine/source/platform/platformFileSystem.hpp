#pragma once

#include "platform/iplatformFileSystem.hpp"

namespace siofraEngine::platform
{
    /**
     * @brief Platform file system
     */
    class PlatformFileSystem : public IPlatformFileSystem
    {
    public:
        /**
         * @brief Read all bytes from a file
         * 
         * @param filePath Path to the file
         * @returns File content bytes
         */
        std::vector<char> readFile(const std::string & filePath) const override;

        /**
         * @brief Read data from a config file
         *
         * @param filePath Path to the config file
         * @returns Config file entries as key value pairs
         */
        std::map<std::string, std::string> readConfigFile(const std::string& filePath) const override;
    };
}
