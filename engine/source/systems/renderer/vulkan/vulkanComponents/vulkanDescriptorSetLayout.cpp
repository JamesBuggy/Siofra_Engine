#include "systems/renderer/vulkan/vulkanComponents/vulkanDescriptorSetLayout.hpp"

namespace siofraEngine::systems
{
    VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout, IVulkanDevice const * device) :
        descriptorSetLayout{descriptorSetLayout},
        device{device}
    {

    }

    VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(VulkanDescriptorSetLayout &&other) noexcept :
        descriptorSetLayout{other.descriptorSetLayout},
        device{other.device}
    {
        other.descriptorSetLayout = VK_NULL_HANDLE;
        other.device = nullptr;
    }

    VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout()
    {
        vkDestroyDescriptorSetLayout(device->getLogicalDevice(), descriptorSetLayout, nullptr);
    }

    VulkanDescriptorSetLayout& VulkanDescriptorSetLayout::operator=(VulkanDescriptorSetLayout &&other) noexcept
    {
        descriptorSetLayout = other.descriptorSetLayout;
        device = other.device;
        other.descriptorSetLayout = VK_NULL_HANDLE;
        other.device = nullptr;
        return *this;
    }

    VulkanDescriptorSetLayout::operator bool() const noexcept
    {
        return descriptorSetLayout != VK_NULL_HANDLE;
    }

    VkDescriptorSetLayout VulkanDescriptorSetLayout::getDescriptorSetLayout() const noexcept
    {
        return descriptorSetLayout;
    }
}
