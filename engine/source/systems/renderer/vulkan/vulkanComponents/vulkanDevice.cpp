#include "systems/renderer/vulkan/vulkanComponents/vulkanDevice.hpp"

namespace siofraEngine::systems
{
    VulkanDevice::VulkanDevice(
        VkPhysicalDevice physicalDevice,
        VkDevice logicalDevice,
        std::unique_ptr<IVulkanQueue> graphicsQueue,
        std::unique_ptr<IVulkanQueue> presentationQueue,
        std::unique_ptr<IVulkanQueue> transferQueue,
        std::unique_ptr<IVulkanQueue> computeQueue) :

        physicalDevice{physicalDevice},
        logicalDevice{logicalDevice},
        graphicsQueue{std::move(graphicsQueue)},
        presentationQueue{std::move(presentationQueue)},
        transferQueue{std::move(transferQueue)},
        computeQueue{std::move(computeQueue)}
    {

    }

    VulkanDevice::VulkanDevice(VulkanDevice &&other) noexcept :
        physicalDevice{other.physicalDevice},
        logicalDevice{other.logicalDevice},
        graphicsQueue{std::move(other.graphicsQueue)},
        presentationQueue{std::move(other.presentationQueue)},
        transferQueue{std::move(other.transferQueue)},
        computeQueue{std::move(other.computeQueue)}
    {
        other.physicalDevice = VK_NULL_HANDLE;
        other.logicalDevice = VK_NULL_HANDLE;
    }

    VulkanDevice::~VulkanDevice()
    {
        vkDestroyDevice(logicalDevice, nullptr);
    }

    VulkanDevice& VulkanDevice::operator=(VulkanDevice &&other) noexcept
    {
        physicalDevice = other.physicalDevice;
        logicalDevice = other.logicalDevice;
        graphicsQueue = std::move(graphicsQueue);
        presentationQueue = std::move(presentationQueue);
        transferQueue = std::move(transferQueue);
        computeQueue = std::move(computeQueue);
        other.physicalDevice = VK_NULL_HANDLE;
        other.logicalDevice = VK_NULL_HANDLE;
        return *this;
    }

    VulkanDevice::operator bool() const noexcept
    {
        return physicalDevice != VK_NULL_HANDLE && logicalDevice != VK_NULL_HANDLE;
    }

    VkPhysicalDevice VulkanDevice::getPhysicalDevice() const noexcept
    {
        return physicalDevice;
    }

    VkDevice VulkanDevice::getLogicalDevice() const noexcept
    {
        return logicalDevice;
    }

    std::unique_ptr<IVulkanQueue> const & VulkanDevice::getGraphicsQueue() const noexcept
    {
        return graphicsQueue;
    }

    std::unique_ptr<IVulkanQueue> const & VulkanDevice::getPresentationQueue() const noexcept
    {
        return presentationQueue;
    }

    std::unique_ptr<IVulkanQueue> const & VulkanDevice::getTransferQueue() const noexcept
    {
        return transferQueue;
    }

    std::unique_ptr<IVulkanQueue> const & VulkanDevice::getComputeQueue() const noexcept
    {
        return computeQueue;
    }
}
