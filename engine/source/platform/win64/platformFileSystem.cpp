#ifdef SE_PLATFORM_WIN64

#include <SDL2/SDL.h>
#include "platform/platformFileSystem.hpp"

namespace siofraEngine::platform
{
    std::vector<char> PlatformFileSystem::readFile(const std::string & filePath) const
    {
        SDL_RWops * io = SDL_RWFromFile(filePath.c_str(), "rb");
        if (io == NULL) {
            throw std::runtime_error("Failed to open file");
        }

        auto size = io->size(io);
        std::vector<char> content(size);
        if (io->read(io, content.data(), 1, size) == 0) {
            throw std::runtime_error("Failed to read file content");
        }
        io->close(io);
        
        return content;
    }
}

#endif
