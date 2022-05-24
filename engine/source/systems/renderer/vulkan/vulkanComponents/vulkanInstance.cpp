#include "systems/renderer/vulkan/vulkanComponents/vulkanInstance.hpp"

namespace siofraEngine::systems
{
    VulkanInstance::VulkanInstance() :
        instance(0)
    {

    }

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

    VkInstance VulkanInstance::getInstance() const noexcept
    {
        return instance;
    }
}