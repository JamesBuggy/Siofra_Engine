#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanInstanceBuilder.hpp"

namespace siofraEngine::systems
{
    VulkanInstance::Builder::Builder() :
		instanceExtensions{}
    {

    }

    VulkanInstance::Builder& VulkanInstance::Builder::withInstanceExtensions(std::vector<const char*> instanceExtensions) noexcept
    {
        this->instanceExtensions = instanceExtensions;
        return *this;
    }

    VulkanInstance VulkanInstance::Builder::build() const
    {
        if (!checkInstanceExtensionSupport(instanceExtensions))
        {
            throw std::runtime_error("VkInstance does not support required extensions");
        }

        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Vulkan App";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
        createInfo.ppEnabledExtensionNames = instanceExtensions.data();

        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
        createInfo.pNext = nullptr;

        VkInstance instance = 0;
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create a Vulkan instance");
        }

        return VulkanInstance(instance);
    }

    bool VulkanInstance::Builder::checkInstanceExtensionSupport(std::vector<const char*> const &checkExtensions) const noexcept
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        for (const auto& checkExtenion : checkExtensions)
        {
            bool hasExtension = false;
            for (const auto& extension : extensions)
            {
                if (strcmp(checkExtenion, extension.extensionName) == 0)
                {
                    hasExtension = true;
                    break;
                }
            }

            if (!hasExtension)
            {
                return false;
            }
        }

        return true;
    }
}