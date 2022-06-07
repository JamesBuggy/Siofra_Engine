#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanFramebufferBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanFramebufferBuilder& VulkanFramebuffer::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    IVulkanFramebufferBuilder& VulkanFramebuffer::Builder::withRenderPassHandle(VkRenderPass renderPassHandle) noexcept
    {
        this->renderPassHandle = renderPassHandle;
        return *this;
    }

    IVulkanFramebufferBuilder& VulkanFramebuffer::Builder::withExtents(uint32_t width, uint32_t height) noexcept
    {
        this->extents = { width, height };
        return *this;
    }

    IVulkanFramebufferBuilder& VulkanFramebuffer::Builder::withAttachment(IVulkanImage const * attachment, FrameBufferAttachmentTypes attachmentType) noexcept
    {
        switch (attachmentType)
        {
        case FrameBufferAttachmentTypes::COLOUR_ATTACHMENT :
            colourAttachment = attachment;
            break;
        case FrameBufferAttachmentTypes::DEPTH_ATTACHMENT :
            depthAttachment = attachment;
            break;
        default:
            throw std::runtime_error("Unsupported framebuffer attachment type");
        }

        return *this;
    }

    std::unique_ptr<IVulkanFramebuffer> VulkanFramebuffer::Builder::build() const
    {
        std::vector<VkImageView> attachments = {
            colourAttachment->getImageView(),
            depthAttachment->getImageView()
        };

        VkFramebufferCreateInfo framebufferCreateInfo = {};
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.renderPass = renderPassHandle;
        framebufferCreateInfo.pAttachments = attachments.data();
        framebufferCreateInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferCreateInfo.width = extents.width;
        framebufferCreateInfo.height = extents.height;
        framebufferCreateInfo.layers = 1;

        VkFramebuffer frameBuffer{ VK_NULL_HANDLE };
        if (vkCreateFramebuffer(device->getLogicalDevice(), &framebufferCreateInfo, nullptr, &frameBuffer) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create frame buffer");
        }

        return std::make_unique<VulkanFramebuffer>(frameBuffer, device);
    }
}
