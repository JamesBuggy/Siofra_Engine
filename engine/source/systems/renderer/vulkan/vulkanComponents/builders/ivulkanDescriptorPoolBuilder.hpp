#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDescriptorPool.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan descriptor pool builder interface
     */
    class IVulkanDescriptorPoolBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the descriptor pool
         * 
         * @param device The device with which to create the descriptor pool
         * @returns Reference to the builder
         */
        virtual IVulkanDescriptorPoolBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Specify a descriptor pool size
         * 
         * @param type The descriptor type
         * @param descriptorCount The number of bytes to allocate for descriptors of the specified type
         * @returns Reference to the builder
         */
        virtual IVulkanDescriptorPoolBuilder& withPoolSize(VkDescriptorType type, uint32_t descriptorCount) noexcept = 0;

        /**
         * @brief Specify the maximum number of descriptor sets that can be allocated from the pool
         * 
         * @param maxSets The maximum number of descriptor sets that can be allocated from the pool
         * @returns Reference to the builder
         */
        virtual IVulkanDescriptorPoolBuilder& withMaxSets(uint32_t maxSets) noexcept = 0;

        /**
         * @brief Build the Vulkan descriptor pool
         * 
         * @returns The final Vulkan descriptor pool
         */
        virtual std::unique_ptr<IVulkanDescriptorPool> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanDescriptorPoolBuilder() = default;
    };
}
