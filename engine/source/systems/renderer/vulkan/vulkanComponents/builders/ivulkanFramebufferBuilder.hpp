#pragma once

#include <memory>
#include "systems/renderer/vulkan/vulkanComponents/ivulkanFramebuffer.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanRenderPass.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanImage.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Supported framebuffer attachment types
     */
    enum class FrameBufferAttachmentTypes
    {
        COLOUR_ATTACHMENT,
        DEPTH_ATTACHMENT
    };

    /**
     * @brief Vulkan framebuffer builder interface
     */
    class IVulkanFramebufferBuilder
    {
    public:
        /**
         * @brief Specify the device with which to create the framebuffer
         * 
         * @param device The device with which to create the framebuffer
         * @returns A reference to the builder
         */
        virtual IVulkanFramebufferBuilder& withDevice(IVulkanDevice const * device) noexcept = 0;

        /**
         * @brief Specify the framebuffer render pass
         * 
         * @param renderPass The framebuffer render pass
         * @returns A reference to the builder
         */
        virtual IVulkanFramebufferBuilder& withRenderPassHandle(VkRenderPass renderPassHandle) noexcept = 0;

        /**
         * @brief Specify the framebuffer extents
         * 
         * @param width The framebuffer width
         * @param height The framebuffer height
         * @returns A reference to the builder
         */
        virtual IVulkanFramebufferBuilder& withExtents(uint32_t width, uint32_t height) noexcept = 0;

        /**
         * @brief Specify a framebuffer attachment
         * 
         * @param attachment The framebuffer attachment
         * @param attachmentType The framebuffer attachment type
         * @returns A reference to the builder
         */
        virtual IVulkanFramebufferBuilder& withAttachment(IVulkanImage const * attachment, FrameBufferAttachmentTypes attachmentType) noexcept = 0;

        /**
         * @brief Build the Vulkan framebuffer
         * 
         * @returns The final Vulkan framebuffer
         */
        virtual std::unique_ptr<IVulkanFramebuffer> build() const = 0;

        /**
         * @brief Interface destructor
         */
        virtual ~IVulkanFramebufferBuilder() = default;
    };
}
