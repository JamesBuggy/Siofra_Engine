#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanFramebuffer.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan framebuffer
     */
    class VulkanFramebuffer : public IVulkanFramebuffer
    {
    public:
        /**
         * @brief VulkanFramebuffer builder
         */
        class Builder;

        /**
         * @brief VulkanFramebuffer constructor
         * 
         * @param Framebuffer Vulkan framebuffer handle
         * @param device Vulkan device used to create the framebuffer
         */
        VulkanFramebuffer(VkFramebuffer Framebuffer, IVulkanDevice const * device);

        /**
         * @brief VulkanFramebuffer copy constructor
         * 
         * @param other VulkanFramebuffer to copy
         */
        VulkanFramebuffer(VulkanFramebuffer const &other) = delete;

        /**
         * @brief VulkanFramebuffer move constructor
         * 
         * @param other VulkanFramebuffer to move
         */
        VulkanFramebuffer(VulkanFramebuffer &&other) noexcept;

        /**
         * @brief VulkanFramebuffer destructor
         */
        ~VulkanFramebuffer();

        /**
         * @brief VulkanFramebuffer copy assignment
         * 
         * @param other VulkanFramebuffer to copy
         */
        VulkanFramebuffer& operator=(const VulkanFramebuffer &other) = delete;

        /**
         * @brief VulkanFramebuffer move assignment
         * 
         * @param other VulkanFramebuffer to move
         */
        VulkanFramebuffer& operator=(VulkanFramebuffer &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;

        /**
         * @brief Get the Vulkan framebuffer handle
         * 
         * @returns The Vulkan framebuffer handle
         */
        VkFramebuffer getFramebuffer() const noexcept override;

    private:
        /**
         * @brief Vulkan framebuffer handle
         */
        VkFramebuffer Framebuffer{ VK_NULL_HANDLE };

        /**
         * @brief Vulkan device used to create the framebuffer
         */
        IVulkanDevice const * device{ nullptr };
    };
}
