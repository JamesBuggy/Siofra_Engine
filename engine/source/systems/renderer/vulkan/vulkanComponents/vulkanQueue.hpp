#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanQueue.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Maintains a vulkan queue handle
     */
    class VulkanQueue : public IVulkanQueue
    {
    public:
        /**
         * @brief VulkanQueue builder
         */
        class Builder;

        /**
         * @brief VulkanQueue constructor
         * 
         * @param queue VkQueue handle
         */
        VulkanQueue(VkQueue queue);

        /**
         * @brief VulkanQueue copy constructor
         * 
         * @param other VulkanQueue to copy
         */
        VulkanQueue(VulkanQueue const &other) = delete;

        /**
         * @brief VulkanQueue move constructor
         * 
         * @param other VulkanQueue to move
         */
        VulkanQueue(VulkanQueue &&other) noexcept;

        /**
         * @brief VulkanQueue destructor
         */
        ~VulkanQueue() = default;

        /**
         * @brief VulkanQueue copy assignment
         * 
         * @param other VulkanQueue to copy
         */
        VulkanQueue& operator=(const VulkanQueue &other) = delete;

        /**
         * @brief VulkanQueue move assignment
         * 
         * @param other VulkanQueue to move
         */
        VulkanQueue& operator=(VulkanQueue &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;

        /**
         * @brief Get the vulkan queue handle
         * 
         * @returns The vulkan queue handle
         */
        VkQueue getQueue() const noexcept override;

    private:
        /**
         * @brief The vulkan queue handle
         */
        VkQueue queue{ VK_NULL_HANDLE };
    };
}
