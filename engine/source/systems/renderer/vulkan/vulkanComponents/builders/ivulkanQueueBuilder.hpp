#pragma once

#include <cstdint>
#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanQueue.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan queue builder interface
     */
    class IVulkanQueueBuilder
    {
    public:
        /**
         * @brief Specify the logical device that owns the queue
         * 
         * @param logicalDevice The logical device that owns the queue
         * @returns Reference to the Vulkan queue builder
         */
        virtual IVulkanQueueBuilder& withLogicalDevice(VkDevice logicalDevice) noexcept = 0;

        /**
         * @brief Specify the index of the queue family to which the queue belongs
         * 
         * @param queueFamilyIndex The index of the queue family to which the queue belongs
         * @returns Reference to the Vulkan queue builder
         */
		virtual IVulkanQueueBuilder& withQueueFamilyIndex(std::uint32_t queueFamilyIndex) noexcept = 0;

        /**
         * @brief Specify the index within this queue family of the queue to retrieve
         * 
         * @param queueIndex The index within this queue family of the queue to retrieve
         * @returns Reference to the Vulkan queue builder
         */
		virtual IVulkanQueueBuilder& withQueueIndex(std::uint32_t queueIndex) noexcept = 0;

        /**
         * @brief Build the Vulkan queue
         * 
         * @returns The final Vulkan queue
         */
        virtual std::unique_ptr<IVulkanQueue> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanQueueBuilder() = default;
    };
}
