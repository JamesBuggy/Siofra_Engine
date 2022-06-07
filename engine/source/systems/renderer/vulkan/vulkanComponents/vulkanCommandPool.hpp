#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanCommandPool.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan command pool
     */
    class VulkanCommandPool : public IVulkanCommandPool
    {
    public:
        /**
         * @brief VulkanCommandPool builder
         */
        class Builder;

        /**
         * @brief VulkanCommandPool constructor
         * 
         * @param commandPool Vulkan command pool handle
         * @param deviceHandle Vulkan device used to create the command pool
         */
        VulkanCommandPool(VkCommandPool commandPool, IVulkanDevice const * device);

        /**
         * @brief VulkanCommandPool copy constructor
         * 
         * @param other VulkanCommandPool to copy
         */
        VulkanCommandPool(VulkanCommandPool const &other) = delete;

        /**
         * @brief VulkanCommandPool move constructor
         * 
         * @param other VulkanCommandPool to move
         */
        VulkanCommandPool(VulkanCommandPool &&other) noexcept;

        /**
         * @brief VulkanCommandPool destructor
         */
        ~VulkanCommandPool();

        /**
         * @brief VulkanCommandPool copy assignment
         * 
         * @param other VulkanCommandPool to copy
         */
        VulkanCommandPool& operator=(const VulkanCommandPool &other) = delete;

        /**
         * @brief VulkanCommandPool move assignment
         * 
         * @param other VulkanCommandPool to move
         */
        VulkanCommandPool& operator=(VulkanCommandPool &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;

        /**
         * @brief Get the Vulkan command pool handle
         * 
         * @returns The Vulkan command pool handle
         */
        VkCommandPool getCommandPool() const noexcept override;

    private:
        /**
         * @brief Vulkan command pool handle
         */
        VkCommandPool commandPool{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan device used to create the command pool
         */
        IVulkanDevice const * device{ nullptr };
    };
}
