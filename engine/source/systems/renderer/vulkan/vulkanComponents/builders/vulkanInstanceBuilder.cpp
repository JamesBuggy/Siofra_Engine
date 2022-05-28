#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanInstanceBuilder.hpp"

namespace siofraEngine::systems
{
    IVulkanInstanceBuilder& VulkanInstance::Builder::withApiVersion(uint32_t major, uint32_t minor) noexcept
    {
        apiMajorVersion = major;
        apiMinorVersion = minor;
        return *this;
    }

    IVulkanInstanceBuilder& VulkanInstance::Builder::withEngineVersion(uint32_t major, uint32_t minor) noexcept
    {
        engineMajorVersion = major;
        engineMinorVersion = minor;
        return *this;
    }

    IVulkanInstanceBuilder& VulkanInstance::Builder::withApplicationVersion(uint32_t major, uint32_t minor) noexcept
    {
        applicationMajorVersion = major;
        applicationMinorVersion = minor;
        return *this;
    }

    IVulkanInstanceBuilder& VulkanInstance::Builder::withInstanceExtensions(std::vector<const char *> instanceExtensions) noexcept
    {
        this->instanceExtensions.insert(this->instanceExtensions.end(), instanceExtensions.begin(), instanceExtensions.end());
        return *this;
    }

    IVulkanInstanceBuilder& VulkanInstance::Builder::withValidationLayers(std::vector<const char*> validationLayers) noexcept
    {
        this->validationLayers.insert(this->validationLayers.end(), validationLayers.begin(), validationLayers.end());
        return *this;
    }

    IVulkanInstanceBuilder& VulkanInstance::Builder::withDebugUtilities() noexcept
    {
        debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugCreateInfo.pfnUserCallback = VulkanInstance::debugCallback;
        debugCreateInfo.pUserData = nullptr;

        instanceExtensions.insert(instanceExtensions.end(), debugExtensions.begin(), debugExtensions.end());
        enableDebugUtilities = true;

        return *this;
    }

    std::unique_ptr<IVulkanInstance> VulkanInstance::Builder::build() const
    {
        if (!checkInstanceExtensionSupport(instanceExtensions))
        {
            throw std::runtime_error("VkInstance does not support required extensions");
        }

        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Vulkan App";
        appInfo.applicationVersion = VK_MAKE_API_VERSION(0, applicationMajorVersion, applicationMinorVersion, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_API_VERSION(0, engineMajorVersion, engineMinorVersion, 0);
        appInfo.apiVersion = VK_MAKE_API_VERSION(0, apiMajorVersion, apiMinorVersion, 0);

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
        createInfo.ppEnabledExtensionNames = instanceExtensions.data();
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        if (enableDebugUtilities)
        {
            createInfo.pNext = &debugCreateInfo;
        }
        else
        {
            createInfo.pNext = nullptr;
        }

        VkInstance instance = VK_NULL_HANDLE;
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create a Vulkan instance");
        }

        VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
        if (enableDebugUtilities && instance != VK_NULL_HANDLE)
        {
            VkResult result = createDebugUtilsMessengerEXT(instance, &debugCreateInfo, nullptr, &debugMessenger);
            if (result != VK_SUCCESS)
            {
                throw std::runtime_error("Failed to create a debug messenger");
            }
        }

        return std::make_unique<VulkanInstance>(instance, debugMessenger);
    }

    bool VulkanInstance::Builder::checkInstanceExtensionSupport(std::vector<const char *> const &checkExtensions) const noexcept
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        for (const auto &checkExtenion : checkExtensions)
        {
            bool hasExtension = false;
            for (const auto &extension : extensions)
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

    VkResult VulkanInstance::Builder::createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger) const noexcept
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }
}
