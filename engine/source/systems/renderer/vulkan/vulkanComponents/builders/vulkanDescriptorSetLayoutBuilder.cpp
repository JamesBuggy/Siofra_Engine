#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanDescriptorSetLayoutBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanDescriptorSetLayoutBuilder& VulkanDescriptorSetLayout::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    IVulkanDescriptorSetLayoutBuilder& VulkanDescriptorSetLayout::Builder::withLayoutBinding(uint32_t binding, VkDescriptorType descriptorType, uint32_t descriptorCount, VkShaderStageFlags stageFlags) noexcept
    {
        VkDescriptorSetLayoutBinding layoutBinding{ };
        layoutBinding.binding = binding;
        layoutBinding.descriptorType = descriptorType;
        layoutBinding.descriptorCount = descriptorCount;
        layoutBinding.stageFlags = stageFlags;
        layoutBinding.pImmutableSamplers = nullptr;
        layoutBindings.push_back(layoutBinding);
        return *this;
    }

    std::unique_ptr<IVulkanDescriptorSetLayout> VulkanDescriptorSetLayout::Builder::build() const
    {
        VkDescriptorSetLayoutCreateInfo layoutCreateInfo{ };
        layoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutCreateInfo.pBindings = layoutBindings.data();
        layoutCreateInfo.bindingCount = static_cast<uint32_t>(layoutBindings.size());

        VkDescriptorSetLayout descriptorSetLayout{ VK_NULL_HANDLE };
        if (vkCreateDescriptorSetLayout(device->getLogicalDevice(), &layoutCreateInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create descriptor set layout");
        }

        return std::make_unique<VulkanDescriptorSetLayout>(descriptorSetLayout, device);
    }
}
