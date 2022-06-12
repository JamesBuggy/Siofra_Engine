#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanSampler.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan sampler
     */
    class VulkanSampler : public IVulkanSampler
    {
    public:
        /**
         * @brief VulkanSampler builder
         */
        class Builder;

        /**
         * @brief VulkanSampler constructor
         * 
         * @param sampler Vulkan sampler handle
         * @param device Vulkan device used to create the sampler
         */
        VulkanSampler(VkSampler sampler, IVulkanDevice const * device);

        /**
         * @brief VulkanSampler copy constructor
         * 
         * @param other VulkanSampler to copy
         */
        VulkanSampler(VulkanSampler const &other) = delete;

        /**
         * @brief VulkanSampler move constructor
         * 
         * @param other VulkanSampler to move
         */
        VulkanSampler(VulkanSampler &&other) noexcept;

        /**
         * @brief VulkanSampler destructor
         */
        ~VulkanSampler();

        /**
         * @brief VulkanSampler copy assignment
         * 
         * @param other VulkanSampler to copy
         */
        VulkanSampler& operator=(const VulkanSampler &other) = delete;

        /**
         * @brief VulkanSampler move assignment
         * 
         * @param other VulkanSampler to move
         */
        VulkanSampler& operator=(VulkanSampler &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;

        /**
         * @brief Get the vulkan sampler handle
         * 
         * @returns The vulkan sampler handle
         */
        VkSampler getSampler() const noexcept override;

    private:
        /**
         * @brief Vulkan sampler handle
         */
        VkSampler sampler{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan device used to create the sampler
         */
        IVulkanDevice const * device{ nullptr };
    };
}
