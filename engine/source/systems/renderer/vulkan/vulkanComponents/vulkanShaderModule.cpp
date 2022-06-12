#include "systems/renderer/vulkan/vulkanComponents/vulkanShaderModule.hpp"

namespace siofraEngine::systems
{
    VulkanShaderModule::VulkanShaderModule(VkShaderModule shaderModule, IVulkanDevice const * device) :
        shaderModule{shaderModule},
        device{device}
    {

    }

    VulkanShaderModule::VulkanShaderModule(VulkanShaderModule &&other) noexcept :
        shaderModule{other.shaderModule},
        device{other.device}
    {
        other.shaderModule = VK_NULL_HANDLE;
        other.device = nullptr;
    }

    VulkanShaderModule::~VulkanShaderModule()
    {
        vkDestroyShaderModule(device->getLogicalDevice(), shaderModule, nullptr);
    }

    VulkanShaderModule& VulkanShaderModule::operator=(VulkanShaderModule &&other) noexcept
    {
        shaderModule = other.shaderModule;
        device = other.device;
        other.shaderModule = VK_NULL_HANDLE;
        other.device = nullptr;
        return *this;
    }

    VulkanShaderModule::operator bool() const noexcept
    {
        return shaderModule != VK_NULL_HANDLE;
    }

    VkShaderModule VulkanShaderModule::getShaderModule() const noexcept
    {
        return shaderModule;
    }
}
