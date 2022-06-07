#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanSemaphore.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan semaphore
     */
    class VulkanSemaphore : public IVulkanSemaphore
    {
    public:
        /**
         * @brief VulkanSemaphore builder
         */
        class Builder;

        /**
         * @brief VulkanSemaphore constructor
         * 
         * @param semaphore Vulkan semaphore handle
         * @param device Vulkan device used to create the semaphore
         */
        VulkanSemaphore(VkSemaphore semaphore, IVulkanDevice const * device);

        /**
         * @brief VulkanSemaphore copy constructor
         * 
         * @param other VulkanSemaphore to copy
         */
        VulkanSemaphore(VulkanSemaphore const &other) = delete;

        /**
         * @brief VulkanSemaphore move constructor
         * 
         * @param other VulkanSemaphore to move
         */
        VulkanSemaphore(VulkanSemaphore &&other) noexcept;

        /**
         * @brief VulkanSemaphore destructor
         */
        ~VulkanSemaphore();

        /**
         * @brief VulkanSemaphore copy assignment
         * 
         * @param other VulkanSemaphore to copy
         */
        VulkanSemaphore& operator=(const VulkanSemaphore &other) = delete;

        /**
         * @brief VulkanSemaphore move assignment
         * 
         * @param other VulkanSemaphore to move
         */
        VulkanSemaphore& operator=(VulkanSemaphore &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;
    
        /**
         * @brief Get the vulkan semaphore handle
         * 
         * @returns The vulkan semaphore handle
         */
        VkSemaphore getSemaphore() const noexcept override;

    private:
        /**
         * @brief Vulkan semaphore handle
         */
        VkSemaphore semaphore{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan device used to create the semaphore
         */
        IVulkanDevice const * device{ nullptr };
    };
}
