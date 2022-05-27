#include "systems/renderer/vulkan/vulkanComponents/vulkanInstance.hpp"

namespace siofraEngine::systems
{
    VulkanInstance::VulkanInstance(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger) :
        instance{instance},
        debugMessenger{debugMessenger}
    {
        
    }

    VulkanInstance::VulkanInstance(VulkanInstance &&other) noexcept :
        instance{other.instance},
        debugMessenger{other.debugMessenger}
    {
        other.instance = VK_NULL_HANDLE;
        other.debugMessenger = VK_NULL_HANDLE;
    }

    VulkanInstance::~VulkanInstance()
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(instance, debugMessenger, nullptr);
        }

        vkDestroyInstance(instance, nullptr);
    }

    VulkanInstance& VulkanInstance::operator=(VulkanInstance &&other) noexcept
    {
        instance = other.instance;
        debugMessenger = other.debugMessenger;
        other.instance = VK_NULL_HANDLE;
        other.debugMessenger = VK_NULL_HANDLE;
        return *this;
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
