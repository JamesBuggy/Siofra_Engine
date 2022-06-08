#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanDescriptorPool.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan descriptor pool
     */
    class VulkanDescriptorPool : public IVulkanDescriptorPool
    {
    public:
        /**
         * @brief VulkanDescriptorPool builder
         */
        class Builder;

        /**
         * @brief VulkanDescriptorPool constructor
         * 
         * @param descriptorPool Vulkan descriptor pool handle
         * @param device Vulkan device used to create the descriptor pool
         */
        VulkanDescriptorPool(VkDescriptorPool descriptorPool, IVulkanDevice const * device);

        /**
         * @brief VulkanDescriptorPool copy constructor
         * 
         * @param other VulkanDescriptorPool to copy
         */
        VulkanDescriptorPool(VulkanDescriptorPool const &other) = delete;

        /**
         * @brief VulkanDescriptorPool move constructor
         * 
         * @param other VulkanDescriptorPool to move
         */
        VulkanDescriptorPool(VulkanDescriptorPool &&other) noexcept;

        /**
         * @brief VulkanDescriptorPool destructor
         */
        ~VulkanDescriptorPool();

        /**
         * @brief VulkanDescriptorPool copy assignment
         * 
         * @param other VulkanDescriptorPool to copy
         */
        VulkanDescriptorPool& operator=(const VulkanDescriptorPool &other) = delete;

        /**
         * @brief VulkanDescriptorPool move assignment
         * 
         * @param other VulkanDescriptorPool to move
         */
        VulkanDescriptorPool& operator=(VulkanDescriptorPool &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;
        
        /**
         * @brief Get the Vulkan descriptor pool handle
         * 
         * @returns The Vulkan descriptor pool handle
         */
        VkDescriptorPool getDescriptorPool() const noexcept override;
    
    private:
        /**
         * @brief Vulkan descriptor pool handle
         */
        VkDescriptorPool descriptorPool{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan device used to create the descriptor pool
         */
        IVulkanDevice const * device{ nullptr };
    };
}
