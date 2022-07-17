#ifdef SE_PLATFORM_WIN64

#include <fstream>
#include <stdexcept>
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

        size_t const objectsToRead = io->size(io);
        size_t const objectSizeBytes = 1;
        std::vector<char> content(objectsToRead);
        if (io->read(io, content.data(), objectSizeBytes, objectsToRead) == 0) {
            throw std::runtime_error("Failed to read file content");
        }
        io->close(io);
        
        return content;
    }

    std::map<std::string, std::string> PlatformFileSystem::readConfigFile(const std::string& filePath) const
    {
        std::ifstream fileStream{ filePath };
        if(!fileStream.is_open())
        {
            throw std::runtime_error("Failed to open config file: " + filePath);
        }

        std::string buffer;
        std::map<std::string, std::string> configEntries{ };
        while(std::getline(fileStream, buffer))
        {
            auto const sepPos = buffer.find('=');
            configEntries.insert({
            	buffer.substr(0, sepPos),
				buffer.substr(sepPos + 1)
			});
            buffer.clear();
	    }

        return configEntries;
    }
}

#endif
