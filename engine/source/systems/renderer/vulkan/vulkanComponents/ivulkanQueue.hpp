#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanSemaphore.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanFence.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanCommandBuffer.hpp"

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
         * @brief Interface destructor
         */
        virtual ~IVulkanQueue() = default;
    };
}
