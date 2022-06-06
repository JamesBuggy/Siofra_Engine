#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanSemaphoreBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanSemaphoreBuilder& VulkanSemaphore::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    std::unique_ptr<IVulkanSemaphore> VulkanSemaphore::Builder::build() const
    {
        VkSemaphoreCreateInfo semephoreCreateInfo{ };
        semephoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkSemaphore semaphore{ VK_NULL_HANDLE };
        if (vkCreateSemaphore(device->getLogicalDevice(), &semephoreCreateInfo, nullptr, &semaphore) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create semephore");
        }

        return std::make_unique<VulkanSemaphore>(semaphore, device);
    }
}
