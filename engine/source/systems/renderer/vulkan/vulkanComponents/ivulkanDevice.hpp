#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanComponent.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanQueue.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan device interface
     */
    class IVulkanDevice : public IVulkanComponent
    {
    public:
        /**
         * @brief Get the physical device handle
         * 
         * @returns The physical device handle
         */
        virtual VkPhysicalDevice getPhysicalDevice() const noexcept = 0;

        /**
         * @brief Get the logical device handle
         * 
         * @returns The logical device handle
         */
        virtual VkDevice getLogicalDevice() const noexcept = 0;

        /**
         * @brief Get the device graphics queue handle
         * 
         * @returns The device graphics queue handle
         */
        virtual std::unique_ptr<IVulkanQueue> const & getGraphicsQueue() const noexcept = 0;

        /**
         * @brief Get the device presentation queue handle
         * 
         * @returns The device presentation queue handle
         */
        virtual std::unique_ptr<IVulkanQueue> const & getPresentationQueue() const noexcept = 0;

        /**
         * @brief Get the device transfer queue handle
         * 
         * @returns The device transfer queue handle
         */
        virtual std::unique_ptr<IVulkanQueue> const & getTransferQueue() const noexcept = 0;

        /**
         * @brief Get the device compute queue handle
         * 
         * @returns The device compute queue handle
         */
        virtual std::unique_ptr<IVulkanQueue> const & getComputeQueue() const noexcept = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanDevice() = default;
    };
}
