#include "systems/renderer/vulkan/vulkanComponents/vulkanDevice.hpp"

namespace siofraEngine::systems
{
        VulkanDevice::VulkanDevice(VkPhysicalDevice physicalDevice, VkDevice logicalDevice) :
            physicalDevice{physicalDevice},
            logicalDevice{logicalDevice}
        {

        }

        VulkanDevice::VulkanDevice(VulkanDevice &&other) noexcept :
            physicalDevice{other.physicalDevice},
            logicalDevice{other.logicalDevice}
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
            other.physicalDevice = VK_NULL_HANDLE;
            other.logicalDevice = VK_NULL_HANDLE;
            return *this;
        }

        VulkanDevice::operator bool() const noexcept
        {
            return physicalDevice != VK_NULL_HANDLE && logicalDevice != VK_NULL_HANDLE;
        }
}
