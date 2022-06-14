#include "systems/renderer/vulkan/vulkanComponents/vulkanQueue.hpp"

namespace siofraEngine::systems
{
    VulkanQueue::VulkanQueue(VkQueue queue, uint32_t familyIndex) :
        queue(queue),
        familyIndex(familyIndex)
    {

    }

    VulkanQueue::VulkanQueue(VulkanQueue &&other) noexcept :
        queue(other.queue),
        familyIndex(other.familyIndex)
    {
        other.queue = VK_NULL_HANDLE;
    }

    VulkanQueue& VulkanQueue::operator=(VulkanQueue &&other) noexcept
    {
        queue = other.queue;
        familyIndex = other.familyIndex;
        other.queue = VK_NULL_HANDLE;
        other.familyIndex = -1;
        return *this;
    }

    VulkanQueue::operator bool() const noexcept
    {
        return queue != VK_NULL_HANDLE;
    }

    VkQueue VulkanQueue::getQueue() const noexcept
    {
        return queue;
    }

    uint32_t VulkanQueue::getFamilyIndex() const noexcept
    {
        return familyIndex;
    }

    void VulkanQueue::submit(IVulkanSemaphore const * waitSemaphore, IVulkanSemaphore const * signalSemaphore, IVulkanFence const * fence, IVulkanCommandBuffer const * commandBuffer) const
    {
        VkPipelineStageFlags waitStages[] = {
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
        };

        VkSemaphore waitSemaphoreHandle = waitSemaphore->getSemaphore();
        VkSemaphore signalSemaphoreHandle = signalSemaphore->getSemaphore();
        VkCommandBuffer commandBufferHandle = commandBuffer->getCommandBuffer();
        VkFence fenceHandle = fence->getFence();

        VkSubmitInfo submitInfo{ };
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.pWaitSemaphores = &waitSemaphoreHandle;
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.pCommandBuffers = &commandBufferHandle;
        submitInfo.commandBufferCount = 1;
        submitInfo.pSignalSemaphores = &signalSemaphoreHandle;
        submitInfo.signalSemaphoreCount = 1;

        if (vkQueueSubmit(queue, 1, &submitInfo, fenceHandle) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to submit command buffer to queue");
        }
    }

    void VulkanQueue::submit(IVulkanCommandBuffer const * commandBuffer) const
    {
        VkCommandBuffer commandBufferHandle = commandBuffer->getCommandBuffer();

        VkSubmitInfo submitInfo{ };
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.pCommandBuffers = &commandBufferHandle;
        submitInfo.commandBufferCount = 1;

        VkResult result = vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to submit command buffer to queue");
        }
    }

    void VulkanQueue::present(IVulkanSemaphore const * waitSemaphore, IVulkanSwapchain const * swapchain, uint32_t imageIndex) const
    {
        VkSemaphore waitSemaphoreHandle = waitSemaphore->getSemaphore();
        VkSwapchainKHR swapchainHandle = swapchain->getSwapchain();

        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.pWaitSemaphores = &waitSemaphoreHandle;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pSwapchains = &swapchainHandle;
        presentInfo.swapchainCount = 1;
        presentInfo.pImageIndices = &imageIndex;

        if (vkQueuePresentKHR(queue, &presentInfo) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to present image");
        }
    }

    void VulkanQueue::waitIdle() const
    {
        vkQueueWaitIdle(queue);
    }
}
