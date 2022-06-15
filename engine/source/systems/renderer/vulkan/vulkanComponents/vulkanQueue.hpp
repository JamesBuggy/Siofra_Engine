#pragma once

#include <stdexcept>
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
         * @param familyIndex The queue family index
         */
        VulkanQueue(VkQueue queue, uint32_t familyIndex);

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

        /**
         * @brief Get the vulkan queue family index
         * 
         * @returns The vulkan queue family index
         */
        uint32_t getFamilyIndex() const noexcept override;

        /**
         * @brief Submits a command buffer to the queue
         * 
         * @param waitSemaphore Semaphore upon which to wait before the command buffer will begin execution
         * @param signalSemaphore Semaphore which will be signaled when the command buffer has completed execution
         * @param fence A fence to be signaled once the submitted command buffer has completed execution
         * @param commandBuffer Command buffer to execute
         */
        void submit(IVulkanSemaphore const * waitSemaphore, IVulkanSemaphore const * signalSemaphore, IVulkanFence const * fence, IVulkanCommandBuffer const * commandBuffer) const override;

        /**
         * @brief Submits a command buffer to the queue
         * 
         * @param commandBuffer Command buffer to execute
         */
        void submit(IVulkanCommandBuffer const * commandBuffer) const override;

        /**
         * @brief Queue an image for presentation
         * 
         * @param waitSemaphore Semaphore to wait for before issuing the present request
         * @param swapchain The swapchain
         * @param imageIndex Index of the swapchain image to present
         */
        void present(IVulkanSemaphore const * waitSemaphore, IVulkanSwapchain const * swapchain, uint32_t imageIndex) const override;

        /**
         * @brief Wait for the queue to become idle
         */
        void waitIdle() const override;

    private:
        /**
         * @brief The vulkan queue handle
         */
        VkQueue queue{ VK_NULL_HANDLE };

        /**
         * @brief The vulkan queue family index
         */
        uint32_t familyIndex{ 0 };
    };
}
