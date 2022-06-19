#pragma once

#include <memory>
#include <string>
#include <algorithm>
#include <cstdint>
#include "core/logging.hpp"
#include "math/math.hpp"
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
         * @param eventSystem Event system
         */
        ResourceSystem(std::unique_ptr<platform::IPlatformFileSystem> fileSystem, systems::IEventSystem * const eventSystem);

        /**
         * @brief Load a shader
         * 
         * @param shaderName The name of the shader file to load
         */
        void loadShader(std::string shaderName);

        /**
         * @brief Load a material
         * 
         * @param materialName The name of the material file to load
         */
        void loadMaterial(std::string materialName);

        /**
         * @brief Load a model
         * 
         * @param modelName The name of the model file to load
         */
        void loadModel(std::string modelName);
    
    private:
        /**
         * @brief Access to platform file system logic
         */
        std::unique_ptr<platform::IPlatformFileSystem> fileSystem{ };

        /**
         * @brief Event system
         */
        systems::IEventSystem * const eventSystem;

        /**
         * @brief Base path of the assets directory
         */
        std::string assetBasePath{ ".\\assets\\" };
    };
}
