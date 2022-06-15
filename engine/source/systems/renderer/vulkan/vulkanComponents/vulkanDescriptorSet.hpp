#pragma once

#include <vector>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDescriptorSet.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan descriptor set
     */
    class VulkanDescriptorSet : public IVulkanDescriptorSet
    {
    public:
        /**
         * @brief VulkanDescriptorSet builder
         */
        class Builder;

        /**
         * @brief VulkanDescriptorSet constructor
         * 
         * @param descriptorSet Vulkan descriptor set handle
         */
        VulkanDescriptorSet(VkDescriptorSet descriptorSet);

        /**
         * @brief VulkanDescriptorSet copy constructor
         * 
         * @param other VulkanDescriptorSet to copy
         */
        VulkanDescriptorSet(VulkanDescriptorSet const &other) = delete;

        /**
         * @brief VulkanDescriptorSet move constructor
         * 
         * @param other VulkanDescriptorSet to move
         */
        VulkanDescriptorSet(VulkanDescriptorSet &&other) noexcept;

        /**
         * @brief VulkanDescriptorSet copy assignment
         * 
         * @param other VulkanDescriptorSet to copy
         */
        VulkanDescriptorSet& operator=(const VulkanDescriptorSet &other) = delete;

        /**
         * @brief VulkanDescriptorSet move assignment
         * 
         * @param other VulkanDescriptorSet to move
         */
        VulkanDescriptorSet& operator=(VulkanDescriptorSet &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;
        
        /**
         * @brief Get the Vulkan descriptor set handle
         * 
         * @returns The Vulkan descriptor set handle
         */
        VkDescriptorSet getDescriptorSet() const noexcept override;

        /**
         * @brief Update the contents of a descriptor set from a buffer
         * 
         * @param buffer The buffer containing the data
         * @param offset The offset in bytes from the start of buffer
         * @param range The size in bytes that is used for this descriptor update
         * @param destinationBinding The descriptor binding within the set
         */
        void updateFromBuffer(IVulkanBuffer const * buffer, VkDeviceSize offset, VkDeviceSize range, uint32_t destinationBinding, IVulkanDevice const * device) const override;

        /**
         * @brief Update the contents of a descriptor set from an image
         * 
         * @param image The image containing the data
         * @param sampler The image sampler
         * @param destinationBinding The descriptor binding within the set
         * @param device The device with which to update the descriptor set
         */
        void updateFromImage(IVulkanImage const * image, IVulkanSampler const * sampler, uint32_t destinationBinding, IVulkanDevice const * device) const override;
    
    private:
    /**
         * @brief Vulkan descriptor set handle
         */
        VkDescriptorSet descriptorSet{ VK_NULL_HANDLE };
    };
}
