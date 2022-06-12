#pragma once

#include <memory>
#include <string>
#include "platform/iplatformFileSystem.hpp"
#include "systems/events/ieventSystem.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Resource system interface
     */
    class ResourceSystem
    {
    public:
        /**
         * @brief ResourceSystem constructor
         * 
         * @param platformInput Access to platform file system logic
         * @param eventSystem Event system reference
         */
        ResourceSystem(std::unique_ptr<platform::IPlatformFileSystem> fileSystem, systems::IEventSystem & eventSystem);

        /**
         * @brief Load a shader
         * 
         * @param shaderName The name of the shader file to load
         */
        void loadShader(std::string shaderName);
    
    private:
        /**
         * @brief Access to platform file system logic
         */
        std::unique_ptr<platform::IPlatformFileSystem> fileSystem{ };

        /**
         * @brief Event system reference
         */
        systems::IEventSystem & eventSystem;

        /**
         * @brief Base path of the assets directory
         */
        std::string assetBasePath{ ".\\assets\\" };
    };
}
