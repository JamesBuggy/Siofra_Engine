#pragma once

#include <stdexcept>
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
    };
}
