#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanFenceBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanFenceBuilder& VulkanFence::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    std::unique_ptr<IVulkanFence> VulkanFence::Builder::build() const
    {
        VkFenceCreateInfo fenceCreateInfo{ };
        fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        VkFence fence{ VK_NULL_HANDLE };
        if (vkCreateFence(device->getLogicalDevice(), &fenceCreateInfo, nullptr, &fence) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create fence");
        }

        return std::make_unique<VulkanFence>(fence, device);
    }
}
