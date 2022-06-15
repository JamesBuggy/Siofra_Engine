#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanSemaphore.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanFence.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanCommandBuffer.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanSwapchain.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan queue interface
     */
    class IVulkanQueue : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the vulkan queue handle
         * 
         * @returns The vulkan queue handle
         */
        virtual VkQueue getQueue() const noexcept = 0;

        /**
         * @brief Get the vulkan queue family index
         * 
         * @returns The vulkan queue family index
         */
        virtual uint32_t getFamilyIndex() const noexcept = 0;

        /**
         * @brief Submits a command buffer to the queue
         * 
         * @param waitSemaphore Semaphore upon which to wait before the command buffer will begin execution
         * @param signalSemaphore Semaphore which will be signaled when the command buffer has completed execution
         * @param fence A fence to be signaled once the submitted command buffer has completed execution
         * @param commandBuffer Command buffer to execute
         */
        virtual void submit(IVulkanSemaphore const * waitSemaphore, IVulkanSemaphore const * signalSemaphore, IVulkanFence const * fence, IVulkanCommandBuffer const * commandBuffer) const = 0;

        /**
         * @brief Submits a command buffer to the queue
         * 
         * @param commandBuffer Command buffer to execute
         */
        virtual void submit(IVulkanCommandBuffer const * commandBuffer) const = 0;

        /**
         * @brief Queue an image for presentation
         * 
         * @param waitSemaphore Semaphore to wait for before issuing the present request
         * @param swapchain The swapchain
         * @param imageIndex Index of the swapchain image to present
         */
        virtual void present(IVulkanSemaphore const * waitSemaphore, IVulkanSwapchain const * swapchain, uint32_t imageIndex) const = 0;

        /**
         * @brief Wait for the queue to become idle
         */
        virtual void waitIdle() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanQueue() = default;
    };
}
