#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDescriptorSet.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDescriptorPool.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDescriptorSetLayout.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan descriptor set builder interface
     */
    class IVulkanDescriptorSetBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the descriptor set
         * 
         * @param device The device with which to create the descriptor set
         * @returns Reference to the builder
         */
        virtual IVulkanDescriptorSetBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Specify the pool which the set will be allocated from
         * 
         * @param descriptorPool The pool which the set will be allocated from
         * @returns Reference to the builder
         */
        virtual IVulkanDescriptorSetBuilder& withDescriptorPool(IVulkanDescriptorPool const * descriptorPool) noexcept = 0;

        /**
         * @brief Specify a descriptor set layout, specifying how the descriptor set is allocated
         * 
         * @param descriptorSetLayout The descriptor set layout
         * @returns Reference to the builder
         */
        virtual IVulkanDescriptorSetBuilder& withDescriptorSetLayout(IVulkanDescriptorSetLayout const * descriptorSetLayout) noexcept = 0;

        /**
         * @brief Build the Vulkan descriptor set
         * 
         * @returns The final Vulkan descriptor set
         */
        virtual std::unique_ptr<IVulkanDescriptorSet> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanDescriptorSetBuilder() = default;
    };
}
