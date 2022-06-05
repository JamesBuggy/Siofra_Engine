#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanCommandPool.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan command pool builder interface
     */
    class IVulkanCommandPoolBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the command pool
         * 
         * @param device The device with which to create the command pool
         * @returns Reference to the builder
         */
        virtual IVulkanCommandPoolBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Specify the command pool create flags
         * 
         * @param flags The command pool create flags
         * @returns Reference to the builder
         */
        virtual IVulkanCommandPoolBuilder& withFlags(VkCommandPoolCreateFlags flags) noexcept = 0;

        /**
         * @brief Specify the command pool queue family index
         * 
         * @param queueFamilyIndex The command pool queue family index
         * @returns Reference to the builder
         */
		virtual IVulkanCommandPoolBuilder& withQueueFamilyIndex(uint32_t queueFamilyIndex) noexcept = 0;

        /**
         * @brief Build the Vulkan command pool
         * 
         * @returns The final Vulkan command pool
         */
        virtual std::unique_ptr<IVulkanCommandPool> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanCommandPoolBuilder() = default;
    };
}
