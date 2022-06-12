#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanShaderModule.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan shader module
     */
    class VulkanShaderModule : public IVulkanShaderModule
    {
    public:
        /**
         * @brief VulkanShaderModule builder
         */
        class Builder;

        /**
         * @brief VulkanShaderModule constructor
         * 
         * @param shaderModule Vulkan shader module handle
         * @param device Vulkan device used to create the shader module
         */
        VulkanShaderModule(VkShaderModule shaderModule, IVulkanDevice const * device);

        /**
         * @brief VulkanShaderModule copy constructor
         * 
         * @param other VulkanShaderModule to copy
         */
        VulkanShaderModule(VulkanShaderModule const &other) = delete;

        /**
         * @brief VulkanShaderModule move constructor
         * 
         * @param other VulkanShaderModule to move
         */
        VulkanShaderModule(VulkanShaderModule &&other) noexcept;

        /**
         * @brief VulkanShaderModule destructor
         */
        ~VulkanShaderModule();

        /**
         * @brief VulkanShaderModule copy assignment
         * 
         * @param other VulkanShaderModule to copy
         */
        VulkanShaderModule& operator=(const VulkanShaderModule &other) = delete;

        /**
         * @brief VulkanShaderModule move assignment
         * 
         * @param other VulkanShaderModule to move
         */
        VulkanShaderModule& operator=(VulkanShaderModule &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;
        
        /**
         * @brief Get the vulkan shader module handle
         * 
         * @returns The vulkan shader module handle
         */
        VkShaderModule getShaderModule() const noexcept override;

    private:
        /**
         * @brief Vulkan shader module handle
         */
        VkShaderModule shaderModule{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan device used to create the shader module
         */
        IVulkanDevice const * device{ nullptr };
    };
}
