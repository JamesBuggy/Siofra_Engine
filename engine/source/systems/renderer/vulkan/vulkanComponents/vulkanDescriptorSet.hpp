#pragma once

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
    
    private:
    /**
         * @brief Vulkan descriptor set handle
         */
        VkDescriptorSet descriptorSet{ VK_NULL_HANDLE };
    };
}
