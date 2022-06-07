#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanFence.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan fence
     */
    class VulkanFence : public IVulkanFence
    {
    public:
        /**
         * @brief VulkanFence builder
         */
        class Builder;

        /**
         * @brief VulkanFence constructor
         * 
         * @param fence Vulkan fence handle
         * @param device Vulkan device used to create the fence
         */
        VulkanFence(VkFence fence, IVulkanDevice const * device);

        /**
         * @brief VulkanFence copy constructor
         * 
         * @param other VulkanFence to copy
         */
        VulkanFence(VulkanFence const &other) = delete;

        /**
         * @brief VulkanFence move constructor
         * 
         * @param other VulkanFence to move
         */
        VulkanFence(VulkanFence &&other) noexcept;

        /**
         * @brief VulkanFence destructor
         */
        ~VulkanFence();

        /**
         * @brief VulkanFence copy assignment
         * 
         * @param other VulkanFence to copy
         */
        VulkanFence& operator=(const VulkanFence &other) = delete;

        /**
         * @brief VulkanFence move assignment
         * 
         * @param other VulkanFence to move
         */
        VulkanFence& operator=(VulkanFence &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;

        /**
         * @brief Get the vulkan fence handle
         * 
         * @returns The vulkan fence handle
         */
        VkFence getFence() const noexcept override;

    private:
        /**
         * @brief Vulkan fence handle
         */
        VkFence fence{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan device used to create the fence
         */
        IVulkanDevice const * device{ nullptr };
    };
}
