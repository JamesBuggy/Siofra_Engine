#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanRenderPassBuilder.hpp"

namespace siofraEngine::systems
{
    VulkanRenderPass::Builder::Builder(IVulkanFramebufferBuilder& vulkanFramebufferBuilder) :
        vulkanFramebufferBuilder{vulkanFramebufferBuilder}
    {

    }

    IVulkanRenderPassBuilder& VulkanRenderPass::Builder::withDevice(IVulkanDevice const * device) noexcept
    {
        this->device = device;
        return *this;
    }

    IVulkanRenderPassBuilder& VulkanRenderPass::Builder::withSwapchain(IVulkanSwapchain const * swapchain) noexcept
    {
        this->swapchain = swapchain;
        return *this;
    }

    IVulkanRenderPassBuilder& VulkanRenderPass::Builder::withColourClearValue(float red, float green, float blue, float alpha) noexcept
    {
        colourClearValue.color = { red, green, blue, alpha };
        return *this;
    }

    IVulkanRenderPassBuilder& VulkanRenderPass::Builder::withDepthClearValue(float depthClearValue) noexcept
    {
        this->depthClearValue.depthStencil.depth = 1.0f;
        return *this;
    }

    std::unique_ptr<IVulkanRenderPass> VulkanRenderPass::Builder::build() const
    {
        std::vector<VkAttachmentDescription> attachments{ };
        
        VkAttachmentDescription colourAttachment{ };
        colourAttachment.format = swapchain->getImageFormat();
        colourAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colourAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colourAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colourAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colourAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colourAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colourAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        attachments.push_back(colourAttachment);

        VkAttachmentReference colourAttachmentReference{ };
        colourAttachmentReference.attachment = attachments.size() - 1;
        colourAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        std::vector<VkAttachmentReference> colourAttachmentReferences{ };
        colourAttachmentReferences.push_back(colourAttachmentReference);

        VkAttachmentDescription depthAttachment{ };
        depthAttachment.format = swapchain->getDepthAttachmentFormat();
        depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        attachments.push_back(depthAttachment);

        VkAttachmentReference depthAttachmentReference{ };
        depthAttachmentReference.attachment = attachments.size() - 1;
        depthAttachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        std::vector<VkSubpassDescription> subpasses{ };

        VkSubpassDescription subpass{ };
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.pColorAttachments = colourAttachmentReferences.data();
        subpass.colorAttachmentCount = static_cast<uint32_t>(colourAttachmentReferences.size());
        subpass.pDepthStencilAttachment = &depthAttachmentReference;

        subpasses.push_back(subpass);

        VkSubpassDependency initialDependency{ };
        initialDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        initialDependency.srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
        initialDependency.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
        initialDependency.dstSubpass = 0;
        initialDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        initialDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        initialDependency.dependencyFlags = 0;

        VkSubpassDependency finalDependency{ };
        finalDependency.srcSubpass = 0;
        finalDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        finalDependency.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        finalDependency.dstSubpass = VK_SUBPASS_EXTERNAL;
        finalDependency.dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
        finalDependency.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
        finalDependency.dependencyFlags = 0;

        std::vector<VkSubpassDependency> subpassDependencies{ };
        subpassDependencies.push_back(initialDependency);
        subpassDependencies.push_back(finalDependency);

        VkRenderPassCreateInfo renderPassCreateInfo{ };
        renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassCreateInfo.pAttachments = attachments.data();
        renderPassCreateInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        renderPassCreateInfo.pSubpasses = subpasses.data();
        renderPassCreateInfo.subpassCount = static_cast<uint32_t>(subpasses.size());
        renderPassCreateInfo.pDependencies = subpassDependencies.data();
        renderPassCreateInfo.dependencyCount = static_cast<uint32_t>(subpassDependencies.size());

        VkOffset2D renderAreaOffset{ 0, 0 };
        VkExtent2D renderAreaExtents{ swapchain->getExtents() };

        VkRenderPass renderPass{ VK_NULL_HANDLE };
        if (vkCreateRenderPass(device->getLogicalDevice(), &renderPassCreateInfo, nullptr, &renderPass) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create render pass");
        }

        std::vector<std::unique_ptr<IVulkanImage>> const & swapchainImages = swapchain->getSwapchainImages();
        std::vector<std::unique_ptr<IVulkanFramebuffer>> framebuffers(swapchainImages.size());
        for(size_t i = 0; i < framebuffers.size(); i++)
        {
            framebuffers[i] = vulkanFramebufferBuilder
                .withAttachment(swapchainImages[i].get(), FrameBufferAttachmentTypes::COLOUR_ATTACHMENT)
                .withAttachment(swapchain->getDepthAttachment().get(), FrameBufferAttachmentTypes::DEPTH_ATTACHMENT)
                .withExtents(renderAreaExtents.width, renderAreaExtents.height)
                .withDevice(device)
                .withRenderPassHandle(renderPass)
                .build();
        }

        std::vector<VkClearValue> clearValues = {
            colourClearValue,
            depthClearValue
        };

        return std::make_unique<VulkanRenderPass>(renderPass, renderAreaOffset, renderAreaExtents, std::move(clearValues), std::move(framebuffers), device);
    }
}
