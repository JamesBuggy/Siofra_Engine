#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanSamplerBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanSamplerBuilder& VulkanSampler::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    std::unique_ptr<IVulkanSampler> VulkanSampler::Builder::build() const
    {
        VkSamplerCreateInfo samplerCreateInfo{ };
        samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerCreateInfo.magFilter = VK_FILTER_LINEAR;
        samplerCreateInfo.minFilter = VK_FILTER_LINEAR;
        samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerCreateInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        samplerCreateInfo.unnormalizedCoordinates = VK_FALSE;
        samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        samplerCreateInfo.mipLodBias = 0.0f;
        samplerCreateInfo.minLod = 0;
        samplerCreateInfo.maxLod = 0;
        samplerCreateInfo.anisotropyEnable = VK_TRUE;
        samplerCreateInfo.maxAnisotropy = 16;

        VkSampler sampler{ VK_NULL_HANDLE };
        if (vkCreateSampler(device->getLogicalDevice(), &samplerCreateInfo, nullptr, &sampler) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create sampler");
        }

        return std::make_unique<VulkanSampler>(sampler, device);
    }
}
