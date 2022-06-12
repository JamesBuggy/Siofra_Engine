#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDescriptorSetLayout.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan descriptor set layout builder interface
     */
    class IVulkanDescriptorSetLayoutBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the descriptor set layout
         * 
         * @param device The device with which to create the descriptor set layout
         * @returns Reference to the builder
         */
        virtual IVulkanDescriptorSetLayoutBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Specify a descriptor set layout binding
         * 
         * @param binding The binding number of this entry and corresponds to a resource of the same binding number in the shader stages
         * @param descriptorType The type of resource descriptors are used for this binding
         * @param descriptorCount The number of descriptors contained in the binding
         * @param stageFlags The pipeline shader stages that can access a resource for this binding
         * @returns Reference to the builder
         */
        virtual IVulkanDescriptorSetLayoutBuilder& withLayoutBinding(uint32_t binding, VkDescriptorType descriptorType, uint32_t descriptorCount, VkShaderStageFlags stageFlags) noexcept = 0;

        /**
         * @brief Build the Vulkan descriptor set layout
         * 
         * @returns The final Vulkan descriptor set layout
         */
        virtual std::unique_ptr<IVulkanDescriptorSetLayout> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanDescriptorSetLayoutBuilder() = default;
    };
}
