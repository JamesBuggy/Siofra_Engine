#pragma once

#include "systems/renderer/vulkan/vulkanComponents/vulkanQueue.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanQueueBuilder.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan queue builder
     */
    class VulkanQueue::Builder : public IVulkanQueueBuilder
    {
    public:
        /**
         * @brief Vulkan queue builder constructor
         */
        Builder() = default;

        /**
         * @brief Specify the logical device that owns the queue
         * 
         * @param logicalDevice The logical device that owns the queue
         * @returns Reference to the Vulkan queue builder
         */
        IVulkanQueueBuilder& withLogicalDevice(VkDevice logicalDevice) noexcept override;

        /**
         * @brief Specify the index of the queue family to which the queue belongs
         * 
         * @param queueFamilyIndex The index of the queue family to which the queue belongs
         * @returns Reference to the Vulkan queue builder
         */
		IVulkanQueueBuilder& withQueueFamilyIndex(std::uint32_t queueFamilyIndex) noexcept override;

        /**
         * @brief Specify the index within this queue family of the queue to retrieve
         * 
         * @param queueIndex The index within this queue family of the queue to retrieve
         * @returns Reference to the Vulkan queue builder
         */
		IVulkanQueueBuilder& withQueueIndex(std::uint32_t queueIndex) noexcept override;

        /**
         * @brief Build the Vulkan queue
         * 
         * @returns The final Vulkan queue
         */
        std::unique_ptr<IVulkanQueue> build() const override;

    private:
        /**
         * @brief The logical device that owns the queue
         */
        VkDevice logicalDevice{ VK_NULL_HANDLE };

        /**
         * @brief The index of the queue family to which the queue belongs
         */
        std::uint32_t queueFamilyIndex{ 0 };

        /**
         * @brief The index within this queue family of the queue to retrieve
         */
        std::uint32_t queueIndex{ 0 };
    };
}
