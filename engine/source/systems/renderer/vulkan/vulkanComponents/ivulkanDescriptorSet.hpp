#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanBuffer.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan descriptor set interface
     */
    class IVulkanDescriptorSet : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the Vulkan descriptor set handle
         * 
         * @returns The Vulkan descriptor set handle
         */
        virtual VkDescriptorSet getDescriptorSet() const noexcept = 0;

        /**
         * @brief Update the contents of a descriptor set from a buffer
         * 
         * @param buffer The buffer containing the data
         * @param offset The offset in bytes from the start of buffer
         * @param range The size in bytes that is used for this descriptor update
         * @param destinationBinding The descriptor binding within the set
         */
        virtual void updateFromBuffer(IVulkanBuffer const * buffer, VkDeviceSize offset, VkDeviceSize range, uint32_t destinationBinding, IVulkanDevice const * device) const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanDescriptorSet() = default;
    };
}
