#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanDescriptorSetLayout.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan descriptor set layout
     */
    class VulkanDescriptorSetLayout : public IVulkanDescriptorSetLayout
    {
    public:
        /**
         * @brief VulkanDescriptorSetLayout builder
         */
        class Builder;

        /**
         * @brief VulkanDescriptorSetLayout constructor
         * 
         * @param descriptorSetLayout Vulkan descriptor set layout handle
         * @param device Vulkan device used to create the descriptor set layout
         */
        VulkanDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout, IVulkanDevice const * device);

        /**
         * @brief VulkanDescriptorSetLayout copy constructor
         * 
         * @param other VulkanDescriptorSetLayout to copy
         */
        VulkanDescriptorSetLayout(VulkanDescriptorSetLayout const &other) = delete;

        /**
         * @brief VulkanDescriptorSetLayout move constructor
         * 
         * @param other VulkanDescriptorSetLayout to move
         */
        VulkanDescriptorSetLayout(VulkanDescriptorSetLayout &&other) noexcept;

        /**
         * @brief VulkanDescriptorSetLayout destructor
         */
        ~VulkanDescriptorSetLayout();

        /**
         * @brief VulkanDescriptorSetLayout copy assignment
         * 
         * @param other VulkanDescriptorSetLayout to copy
         */
        VulkanDescriptorSetLayout& operator=(const VulkanDescriptorSetLayout &other) = delete;

        /**
         * @brief VulkanDescriptorSetLayout move assignment
         * 
         * @param other VulkanDescriptorSetLayout to move
         */
        VulkanDescriptorSetLayout& operator=(VulkanDescriptorSetLayout &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;

        /**
         * @brief Get the Vulkan descriptor set layout handle
         * 
         * @returns The Vulkan descriptor set layout handle
         */
        VkDescriptorSetLayout getDescriptorSetLayout() const noexcept override;

    private:
        /**
         * @brief Vulkan descriptor set layout handle
         */
        VkDescriptorSetLayout descriptorSetLayout{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan device used to create the descriptor set layout
         */
        IVulkanDevice const * device{ nullptr };
    };
}
