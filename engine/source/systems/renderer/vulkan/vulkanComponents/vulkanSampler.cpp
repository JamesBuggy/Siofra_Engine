#include "systems/renderer/vulkan/vulkanComponents/vulkanSampler.hpp"

namespace siofraEngine::systems
{
    VulkanSampler::VulkanSampler(VkSampler sampler, IVulkanDevice const * device) :
        sampler{sampler},
        device{device}
    {
        
    }

    VulkanSampler::VulkanSampler(VulkanSampler &&other) noexcept :
        sampler{other.sampler},
        device{other.device}
    {
        other.sampler = VK_NULL_HANDLE;
        other.device = nullptr;
    }

    VulkanSampler::~VulkanSampler()
    {
        vkDestroySampler(device->getLogicalDevice(), sampler, nullptr);
    }

    VulkanSampler& VulkanSampler::operator=(VulkanSampler &&other) noexcept
    {
        sampler = other.sampler;
        device = other.device;
        other.sampler = VK_NULL_HANDLE;
        other.device = nullptr;
        return *this;
    }

    VulkanSampler::operator bool() const noexcept
    {
        return sampler != VK_NULL_HANDLE;
    }

    VkSampler VulkanSampler::getSampler() const noexcept
    {
        return sampler;
    }
}
