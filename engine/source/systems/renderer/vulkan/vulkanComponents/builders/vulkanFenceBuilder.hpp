#pragma once

#include <stdexcept>
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanFenceBuilder.hpp"
#include "systems/renderer/vulkan/vulkanComponents/vulkanFence.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan fence builder
     */
    class VulkanFence::Builder : public IVulkanFenceBuilder
    {
    public:
        /**
         * @brief Specify the device used to create the fence
         * 
         * @param device The device with which to create the fence
         * @returns Reference to the builder
         */
        IVulkanFenceBuilder& withDevice(IVulkanDevice const * device) noexcept override;

        /**
         * @brief Build the Vulkan fence
         * 
         * @returns The final Vulkan fence
         */
        std::unique_ptr<IVulkanFence> build() const override;

    private:
        /**
         * @brief The device with which to create the fence
         */
        IVulkanDevice const * device{ nullptr };
    };
}
