#include "systems/renderer/vulkan/vulkanComponents/vulkanDescriptorSet.hpp"

namespace siofraEngine::systems
{
    VulkanDescriptorSet::VulkanDescriptorSet(VkDescriptorSet descriptorSet) :
        descriptorSet{descriptorSet}
    {

    }

    VulkanDescriptorSet::VulkanDescriptorSet(VulkanDescriptorSet &&other) noexcept :
        descriptorSet{other.descriptorSet}
    {
        other.descriptorSet = VK_NULL_HANDLE;
    }

    VulkanDescriptorSet& VulkanDescriptorSet::operator=(VulkanDescriptorSet &&other) noexcept
    {
        descriptorSet = other.descriptorSet;
        other.descriptorSet = VK_NULL_HANDLE;
        return *this;
    }

    VulkanDescriptorSet::operator bool() const noexcept
    {
        return descriptorSet != VK_NULL_HANDLE;
    }

    VkDescriptorSet VulkanDescriptorSet::getDescriptorSet() const noexcept
    {
        return descriptorSet;
    }
}
