#pragma once

#include "core/logging.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanInstance.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanSurface.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Maintains a vulkan surface handle
     */
    class VulkanSurface : public IVulkanSurface
    {
    public:
        /**
         * @brief VulkanSurface builder
         */
        class Builder;

        /**
         * @brief VulkanSurface constructor
         * 
         * @param surface Vulkan surface handle
         * @param instance Vulkan instance to which the surface relates
         */
        VulkanSurface(VkSurfaceKHR surface, IVulkanInstance const *instance);

        /**
         * @brief VulkanSurface copy constructor
         * 
         * @param other VulkanSurface to copy
         */
        VulkanSurface(VulkanSurface const &other) = delete;

        /**
         * @brief VulkanSurface move constructor
         * 
         * @param other VulkanSurface to move
         */
        VulkanSurface(VulkanSurface &&other) noexcept;

        /**
         * @brief VulkanSurface destructor
         */
        ~VulkanSurface();

        /**
         * @brief VulkanSurface copy assignment
         * 
         * @param other VulkanSurface to copy
         */
        VulkanSurface& operator=(const VulkanSurface &other) = delete;

        /**
         * @brief VulkanSurface move assignment
         * 
         * @param other VulkanSurface to move
         */
        VulkanSurface& operator=(VulkanSurface &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;

        /**
         * @brief Get the vulkan surface handle
         * 
         * @returns The vulkan surface handle
         */
        VkSurfaceKHR getSurface() const noexcept override;

    private:
        /**
         * @brief The vulkan surface handle
         */
        VkSurfaceKHR surface{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan instance to which the surface relates
         */
        IVulkanInstance const * instance{ nullptr };
    };
}
