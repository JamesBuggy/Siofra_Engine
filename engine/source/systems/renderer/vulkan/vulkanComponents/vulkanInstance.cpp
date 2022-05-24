#include "systems/renderer/vulkan/vulkanComponents/vulkanInstance.hpp"

namespace siofraEngine::systems
{
    VulkanInstance::VulkanInstance(VkInstance instance) :
        instance(instance)
    {

    }

    VulkanInstance::~VulkanInstance()
    {

    }

    void VulkanInstance::destroy()
    {
        vkDestroyInstance(instance, nullptr);
    }

    VulkanInstance::operator bool() const noexcept
    {
        return instance != VK_NULL_HANDLE;
    }

    VkInstance VulkanInstance::getInstance() const noexcept
    {
        return instance;
    }
}