#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanDescriptorPoolBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanDescriptorPoolBuilder& VulkanDescriptorPool::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    IVulkanDescriptorPoolBuilder& VulkanDescriptorPool::Builder::withPoolSize(VkDescriptorType type, uint32_t descriptorCount) noexcept
    {
        VkDescriptorPoolSize poolSize{ };
        poolSize.type = type;
        poolSize.descriptorCount = descriptorCount;
        poolSizes.push_back(poolSize);
        return *this;
    }

    IVulkanDescriptorPoolBuilder& VulkanDescriptorPool::Builder::withMaxSets(uint32_t maxSets) noexcept
    {
        this->maxSets = maxSets;
        return *this;
    }

    std::unique_ptr<IVulkanDescriptorPool> VulkanDescriptorPool::Builder::build() const
    {
        VkDescriptorPoolCreateInfo poolCreateInfo{ };
        poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolCreateInfo.maxSets = maxSets;
        poolCreateInfo.pPoolSizes = poolSizes.data();
        poolCreateInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());

        VkDescriptorPool descriptorPool{ VK_NULL_HANDLE };
        if (vkCreateDescriptorPool(device->getLogicalDevice(), &poolCreateInfo, nullptr, &descriptorPool) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create descriptor pool");
        }

        return std::make_unique<VulkanDescriptorPool>(descriptorPool, device);
    }
}
