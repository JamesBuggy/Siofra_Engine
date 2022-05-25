#include "systems/renderer/vulkan/vulkanComponents/vulkanInstance.hpp"

namespace siofraEngine::systems
{
    VulkanInstance::VulkanInstance(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger) :
        instance{instance},
        debugMessenger{debugMessenger}
    {

    }

    void VulkanInstance::destroy()
    {
        if (debugMessenger != VK_NULL_HANDLE)
        {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
            if (func != nullptr)
            {
                func(instance, debugMessenger, nullptr);
            }
        }

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