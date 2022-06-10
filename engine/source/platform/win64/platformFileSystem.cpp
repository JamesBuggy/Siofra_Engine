#ifdef SE_PLATFORM_WIN64

#include <SDL2/SDL.h>
#include "platform/platformFileSystem.hpp"

namespace siofraEngine::platform
{
    std::vector<char> PlatformFileSystem::readFile(const std::string & filePath) const
    {
        SDL_RWops * io = SDL_RWFromFile(filePath.c_str(), "rb");
        if (io == nullptr) {
            throw std::runtime_error("Failed to open file");
        }

        Sint64 objectsToRead = io->size(io);
        size_t objectSizeBytes = 1;
        std::vector<char> content(objectsToRead);
        if (io->read(io, content.data(), objectSizeBytes, objectsToRead) == 0) {
            throw std::runtime_error("Failed to read file content");
        }
        io->close(io);
        
        return content;
    }
}

#endif
