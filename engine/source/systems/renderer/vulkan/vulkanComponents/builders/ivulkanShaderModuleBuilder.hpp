#pragma once

#include <memory>
#include <vector>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanShaderModule.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan shader module builder interface
     */
    class IVulkanShaderModuleBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the buffer
         * 
         * @param device The device with which to create the buffer
         * @returns Reference to the builder
         */
        virtual IVulkanShaderModuleBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;
        
        /**
         * @brief Provide the compiled spir-v code for the shader
         * 
         * @param shaderCode The compiled spir-v code for the shader
         * @returns Reference to the builder
         */
        virtual IVulkanShaderModuleBuilder& withShaderCode(std::vector<char> shaderCode) noexcept = 0;

        /**
         * @brief Build the Vulkan shader module
         * 
         * @returns The final Vulkan shader module
         */
        virtual std::unique_ptr<IVulkanShaderModule> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanShaderModuleBuilder() = default;
    };
}
