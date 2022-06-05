#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanCommandPoolBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanCommandPool.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan command pool builder
     */
    class VulkanCommandPool::Builder : public IVulkanCommandPoolBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the command pool
         * 
         * @param deviceHandle The device with which to create the command pool
         * @returns Reference to the builder
         */
        IVulkanCommandPoolBuilder& withDevice(IVulkanDevice const * device) noexcept override;

        /**
         * @brief Specify the command pool create flags
         * 
         * @param flags The command pool create flags
         * @returns Reference to the builder
         */
        IVulkanCommandPoolBuilder& withFlags(VkCommandPoolCreateFlags flags) noexcept override;

        /**
         * @brief Specify the command pool queue family index
         * 
         * @param queueFamilyIndex The command pool queue family index
         * @returns Reference to the builder
         */
		IVulkanCommandPoolBuilder& withQueueFamilyIndex(uint32_t queueFamilyIndex) noexcept override;

        /**
         * @brief Build the Vulkan command pool
         * 
         * @returns The final Vulkan command pool
         */
        std::unique_ptr<IVulkanCommandPool> build() const override;
    
    private:
        /**
         * @brief The device with which to create the command pool
         */
        IVulkanDevice const * device{ nullptr };

        /**
         * @brief The command pool create flags
         */
        VkCommandPoolCreateFlags flags{ VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT };

        /**
         * @brief The command pool queue family index
         */
        uint32_t queueFamilyIndex{ 0 };
    };
}
