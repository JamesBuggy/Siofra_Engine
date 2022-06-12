#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanDescriptorPoolBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanDescriptorPool.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan descriptor pool builder
     */
    class VulkanDescriptorPool::Builder : public IVulkanDescriptorPoolBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the descriptor pool
         * 
         * @param device The device with which to create the descriptor pool
         * @returns Reference to the builder
         */
        IVulkanDescriptorPoolBuilder& withDevice(IVulkanDevice const * device) noexcept override;

        /**
         * @brief Specify a descriptor pool size
         * 
         * @param type The descriptor type
         * @param descriptorCount The number of bytes to allocate for descriptors of the specified type
         * @returns Reference to the builder
         */
        IVulkanDescriptorPoolBuilder& withPoolSize(VkDescriptorType type, uint32_t descriptorCount) noexcept override;

        /**
         * @brief Specify the maximum number of descriptor sets that can be allocated from the pool
         * 
         * @param maxSets The maximum number of descriptor sets that can be allocated from the pool
         * @returns Reference to the builder
         */
        IVulkanDescriptorPoolBuilder& withMaxSets(uint32_t maxSets) noexcept override;

        /**
         * @brief Build the Vulkan descriptor pool
         * 
         * @returns The final Vulkan descriptor pool
         */
        std::unique_ptr<IVulkanDescriptorPool> build() const override;
    
    private:
        /**
         * @brief The device with which to create the descriptor pool
         */
        IVulkanDevice const * device{ nullptr };
    
        /**
         * @brief The descriptor pool sizes
         */
        std::vector<VkDescriptorPoolSize> poolSizes{ };

        /**
         * @brief The maximum number of descriptor sets that can be allocated from the pool
         */
        uint32_t maxSets{ 0 };
    };
}
