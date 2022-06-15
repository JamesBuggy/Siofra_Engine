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

    void VulkanDescriptorSet::updateFromBuffer(IVulkanBuffer const * buffer, VkDeviceSize offset, VkDeviceSize range, uint32_t destinationBinding, IVulkanDevice const * device) const
    {
        VkDescriptorBufferInfo vpBufferInfo = {};
        vpBufferInfo.buffer = buffer->getBuffer();
        vpBufferInfo.offset = offset;
        vpBufferInfo.range = range;

        VkWriteDescriptorSet vpSetWrite = {};
        vpSetWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        vpSetWrite.dstSet = descriptorSet;
        vpSetWrite.dstBinding = destinationBinding;
        vpSetWrite.dstArrayElement = 0;
        vpSetWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        vpSetWrite.descriptorCount = 1;
        vpSetWrite.pBufferInfo = &vpBufferInfo;

        std::vector<VkWriteDescriptorSet> descriptorSetWrites = {
            vpSetWrite
        };

        vkUpdateDescriptorSets(device->getLogicalDevice(), static_cast<uint32_t>(descriptorSetWrites.size()), descriptorSetWrites.data(), 0, nullptr);
    }

    void VulkanDescriptorSet::updateFromImage(IVulkanImage const * image, IVulkanSampler const * sampler, uint32_t destinationBinding, IVulkanDevice const * device) const
    {
        VkDescriptorImageInfo imageInfo{ };
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		imageInfo.imageView = image->getImageView();
		imageInfo.sampler = sampler->getSampler();

		VkWriteDescriptorSet descriptorWrite{ };
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = descriptorSet;
		descriptorWrite.dstBinding = destinationBinding;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pImageInfo = &imageInfo;

		vkUpdateDescriptorSets(device->getLogicalDevice(), 1, &descriptorWrite, 0, nullptr);
    }
}
