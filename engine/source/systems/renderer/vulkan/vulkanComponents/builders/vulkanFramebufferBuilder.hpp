#pragma once

#include <stdexcept>
#include <vector>
#include "systems/renderer/vulkan/vulkanComponents/vulkanFramebuffer.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/ivulkanFramebufferBuilder.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Vulkan framebuffer builder interface
     */
    class VulkanFramebuffer::Builder : public IVulkanFramebufferBuilder
    {
    public:
        /**
         * @brief Specify the device with which to create the framebuffer
         * 
         * @param device The device with which to create the framebuffer
         * @returns A reference to the builder
         */
        IVulkanFramebufferBuilder& withDevice(IVulkanDevice const * device) noexcept override;

        /**
         * @brief Specify the framebuffer render pass
         * 
         * @param renderPass The framebuffer render pass
         * @returns A reference to the builder
         */
        IVulkanFramebufferBuilder& withRenderPassHandle(VkRenderPass renderPassHandle) noexcept override;

        /**
         * @brief Specify the framebuffer extents
         * 
         * @param width The framebuffer width
         * @param height The framebuffer height
         * @returns A reference to the builder
         */
        IVulkanFramebufferBuilder& withExtents(uint32_t width, uint32_t height) noexcept override;

        /**
         * @brief Specify a framebuffer attachment
         * 
         * @param attachment The framebuffer attachment
         * @param attachmentType The framebuffer attachment type
         * @returns A reference to the builder
         */
        IVulkanFramebufferBuilder& withAttachment(IVulkanImage const * attachment, FrameBufferAttachmentTypes attachmentType) noexcept override;

        /**
         * @brief Build the Vulkan framebuffer
         * 
         * @returns The final Vulkan framebuffer
         */
        std::unique_ptr<IVulkanFramebuffer> build() const override;

    private:
        /**
         * @brief The device with which to create the framebuffer
         */
        IVulkanDevice const * device{ nullptr };

        /**
         * @brief The framebuffer render pass handle
         */
        VkRenderPass renderPassHandle{ VK_NULL_HANDLE };

        /**
         * @brief The framebuffer colour attachment
         */
        IVulkanImage const * colourAttachment{ nullptr };

        /**
         * @brief The framebuffer depth attachment
         */
        IVulkanImage const * depthAttachment{ nullptr };

        /**
         * @brief The framebuffer extents
         */
        VkExtent2D extents{ 0, 0 };
    };
}
