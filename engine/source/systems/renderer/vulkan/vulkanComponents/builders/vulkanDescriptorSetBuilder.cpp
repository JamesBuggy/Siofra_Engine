#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanDescriptorSetBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanDescriptorSetBuilder& VulkanDescriptorSet::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    IVulkanDescriptorSetBuilder& VulkanDescriptorSet::Builder::withDescriptorPool(IVulkanDescriptorPool const * descriptorPool) noexcept
    {
        this->descriptorPool = descriptorPool;
        return *this;
    }

    IVulkanDescriptorSetBuilder& VulkanDescriptorSet::Builder::withDescriptorSetLayout(IVulkanDescriptorSetLayout const * descriptorSetLayout) noexcept
    {
        this->descriptorSetLayout = descriptorSetLayout;
        return *this;
    }

    std::unique_ptr<IVulkanDescriptorSet> VulkanDescriptorSet::Builder::build() const
    {
        VkDescriptorSetLayout descriptorSetLayoutHandle = descriptorSetLayout->getDescriptorSetLayout();

        VkDescriptorSetAllocateInfo setAllocInfo{ };
        setAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        setAllocInfo.descriptorPool = descriptorPool->getDescriptorPool();
        setAllocInfo.descriptorSetCount = 1;
        setAllocInfo.pSetLayouts = &descriptorSetLayoutHandle;

        VkDescriptorSet descriptorSet{ VK_NULL_HANDLE };
        if (vkAllocateDescriptorSets(device->getLogicalDevice(), &setAllocInfo, &descriptorSet) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to allocate descriptor set");
        }

        return std::make_unique<VulkanDescriptorSet>(descriptorSet);
    }
}
