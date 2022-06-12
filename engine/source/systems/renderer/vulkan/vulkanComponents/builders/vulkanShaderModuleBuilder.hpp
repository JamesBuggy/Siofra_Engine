#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanShaderModuleBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanShaderModule.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan shader module builder interface
     */
    class VulkanShaderModule::Builder : public IVulkanShaderModuleBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the buffer
         * 
         * @param device The device with which to create the buffer
         * @returns Reference to the builder
         */
        IVulkanShaderModuleBuilder& withDevice(IVulkanDevice const * device) noexcept override;
        
        /**
         * @brief Provide the compiled spir-v code for the shader
         * 
         * @param shaderCode The compiled spir-v code for the shader
         * @returns Reference to the builder
         */
        IVulkanShaderModuleBuilder& withShaderCode(std::vector<char> shaderCode) noexcept override;

        /**
         * @brief Build the Vulkan shader module
         * 
         * @returns The final Vulkan shader module
         */
        std::unique_ptr<IVulkanShaderModule> build() const override;

    private:
        /**
         * @brief The device with which to create the buffer
         */
        IVulkanDevice const * device{ nullptr };

        /**
         * @brief The compiled spir-v code for the shader
         */
        std::vector<char> shaderCode{ };
    };
}
