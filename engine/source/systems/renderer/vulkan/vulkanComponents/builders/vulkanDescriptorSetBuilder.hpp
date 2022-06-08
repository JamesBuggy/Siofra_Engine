#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanDescriptorSetBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanDescriptorSet.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan descriptor set builder
     */
    class VulkanDescriptorSet::Builder : public IVulkanDescriptorSetBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the descriptor set
         * 
         * @param device The device with which to create the descriptor set
         * @returns Reference to the builder
         */
        IVulkanDescriptorSetBuilder& withDevice(IVulkanDevice const * device) noexcept override;

        /**
         * @brief Specify the pool which the set will be allocated from
         * 
         * @param descriptorPool The pool which the set will be allocated from
         * @returns Reference to the builder
         */
        IVulkanDescriptorSetBuilder& withDescriptorPool(IVulkanDescriptorPool const * descriptorPool) noexcept override;

        /**
         * @brief Specify a descriptor set layout, specifying how the descriptor set is allocated
         * 
         * @param descriptorSetLayout The descriptor set layout
         * @returns Reference to the builder
         */
        IVulkanDescriptorSetBuilder& withDescriptorSetLayout(IVulkanDescriptorSetLayout const * descriptorSetLayout) noexcept override;

        /**
         * @brief Build the Vulkan descriptor set
         * 
         * @returns The final Vulkan descriptor set
         */
        std::unique_ptr<IVulkanDescriptorSet> build() const override;

    private:
        /**
         * @brief The device with which to create the descriptor set
         */
        IVulkanDevice const * device{ nullptr };

        /**
         * @brief The pool which the set will be allocated from
         */
        IVulkanDescriptorPool const * descriptorPool{ nullptr };

        /**
         * @brief The descriptor set layout, specifying how the descriptor set is allocated
         */
        IVulkanDescriptorSetLayout const * descriptorSetLayout{ nullptr };
    };
}
