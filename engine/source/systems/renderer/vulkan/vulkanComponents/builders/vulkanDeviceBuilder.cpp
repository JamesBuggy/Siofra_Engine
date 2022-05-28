#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanDeviceBuilder.hpp"

namespace siofraEngine::systems
{
    VulkanDevice::Builder::Builder(IVulkanQueueBuilder& vulkanQueueBuilder) :
        vulkanQueueBuilder{vulkanQueueBuilder}
    {

    }

    IVulkanDeviceBuilder& VulkanDevice::Builder::withApiVersionSupport(uint32_t major, uint32_t minor) noexcept
    {
        apiMinimumMajorVersion = major;
        apiMinimumMinorVersion = minor;
        return *this;
    }

    IVulkanDeviceBuilder& VulkanDevice::Builder::withQueueFamilySupport(VulkanDeviceQueueFamilies requiredQueueFamilies) noexcept
    {
        this->requiredQueueFamilies = requiredQueueFamilies;
        return *this;
    }

    IVulkanDeviceBuilder& VulkanDevice::Builder::withExtensionSupport(std::vector<const char*> requiredExtensions) noexcept
    {
        this->requiredDeviceExtensions.insert(this->requiredDeviceExtensions.end(), requiredExtensions.begin(), requiredExtensions.end());
        return *this;
    }

    IVulkanDeviceBuilder& VulkanDevice::Builder::withSurfacePresentationSupport(IVulkanSurface const *surface) noexcept
    {
        this->surface = surface;
        return *this;
    }

    IVulkanDeviceBuilder& VulkanDevice::Builder::withInstance(IVulkanInstance const *instance) noexcept
    {
        this->instance = instance;
        return *this;
    }

    IVulkanDeviceBuilder& VulkanDevice::Builder::withValidationLayers(std::vector<const char*> validationLayers) noexcept
    {
        this->validationLayers = validationLayers;
        return *this;
    }

    std::unique_ptr<IVulkanDevice> VulkanDevice::Builder::build() const
    {
        VkPhysicalDevice physicalDevice = findPhysicalDevice(instance, surface, requiredQueueFamilies, requiredDeviceExtensions);
        VulkanDevice::Builder::QueueFamilyIndicies queueFamilyIndicies = findDeviceQueueFamilyIndicies(physicalDevice, surface);
        VkDevice logicalDevice = createLogicalDevice(physicalDevice, validationLayers, requiredDeviceExtensions, queueFamilyIndicies);

        vulkanQueueBuilder
            .withLogicalDevice(logicalDevice)
            .withQueueIndex(0);

        return std::make_unique<VulkanDevice>(
            physicalDevice,
            logicalDevice,
            vulkanQueueBuilder.withQueueFamilyIndex(queueFamilyIndicies.graphics).build(),
            vulkanQueueBuilder.withQueueFamilyIndex(queueFamilyIndicies.presentation).build(),
            vulkanQueueBuilder.withQueueFamilyIndex(queueFamilyIndicies.transfer).build(),
            vulkanQueueBuilder.withQueueFamilyIndex(queueFamilyIndicies.compute).build());
    }

    VkPhysicalDevice VulkanDevice::Builder::findPhysicalDevice(IVulkanInstance const *instance, IVulkanSurface const *surface, VulkanDeviceQueueFamilies const requiredQueueFamilies, std::vector<const char*> const requiredDeviceExtensions) const
    {
        uint32_t physicalDeviceCount{ 0 };
        vkEnumeratePhysicalDevices(instance->getInstance(), &physicalDeviceCount, nullptr);

        std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
        vkEnumeratePhysicalDevices(instance->getInstance(), &physicalDeviceCount, physicalDevices.data());

        VkPhysicalDevice chosenPhysicalDevice = VK_NULL_HANDLE;
        for (const auto& physicalDevice : physicalDevices)
        {
            if(!findDeviceQueueFamilyIndicies(physicalDevice, surface).areValid(requiredQueueFamilies) ||
                !checkPhysicalDeviceExtensionSupport(physicalDevice, requiredDeviceExtensions) ||
                !checkPhysicalDeviceSwapchainSupport(physicalDevice, surface))
            {
                continue;
            }
            
            chosenPhysicalDevice = physicalDevice;
        }

        if (chosenPhysicalDevice == VK_NULL_HANDLE)
        {
            throw std::runtime_error("No supported physical device found");
        }

        return chosenPhysicalDevice;
    }

    VkDevice VulkanDevice::Builder::createLogicalDevice(VkPhysicalDevice const physicalDevice, std::vector<const char*> const validationLayers, std::vector<const char*> requiredDeviceExtensions, QueueFamilyIndicies const queueFamilyIdicies) const
    {
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{ };

        std::set<int32_t> indicies{ };
        if(queueFamilyIdicies.graphics >= 0) { indicies.insert(queueFamilyIdicies.graphics); }
        if(queueFamilyIdicies.presentation >= 0) { indicies.insert(queueFamilyIdicies.presentation); }
        if(queueFamilyIdicies.transfer >= 0) { indicies.insert(queueFamilyIdicies.transfer); }
        if(queueFamilyIdicies.compute >= 0) { indicies.insert(queueFamilyIdicies.compute); }

        for (uint32_t const &queueFamilyIndex : indicies)
        {
            float priority = 1.0f;
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &priority;

            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{ };
        deviceFeatures.samplerAnisotropy = VK_TRUE;

        VkDeviceCreateInfo deviceCreateInfo{ };
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
        deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredDeviceExtensions.size());
        deviceCreateInfo.ppEnabledExtensionNames = requiredDeviceExtensions.data();
        deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

        if (validationLayers.size() > 0) {
            deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            deviceCreateInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else {
            deviceCreateInfo.enabledLayerCount = 0;
            deviceCreateInfo.ppEnabledLayerNames = nullptr;
        }

        VkDevice logicalDevice{ VK_NULL_HANDLE };
        VkResult result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &logicalDevice);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create a logical device");
        }

        return logicalDevice;
    }

    VulkanDevice::Builder::QueueFamilyIndicies VulkanDevice::Builder::findDeviceQueueFamilyIndicies(VkPhysicalDevice const physicalDevice, IVulkanSurface const *surface) const
    {
        QueueFamilyIndicies queueFamilyIndicies{ };

        uint32_t queuefamilyCount{ 0 };
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queuefamilyCount, nullptr);
        
        std::vector<VkQueueFamilyProperties> queueFamilyList(queuefamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queuefamilyCount, queueFamilyList.data());

        uint32_t queuefamilyIndex{ 0 };
        for (const auto& queuefamily : queueFamilyList)
        {
            if (queuefamily.queueCount > 0 && queuefamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                queueFamilyIndicies.graphics = queuefamilyIndex;
            }

            VkBool32 presentationSupport{ false };
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queuefamilyIndex, surface->getSurface(), &presentationSupport);
            if (queuefamily.queueCount > 0 && presentationSupport)
            {
                queueFamilyIndicies.presentation = queuefamilyIndex;
            }

            if (queuefamily.queueCount > 0 && queuefamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
            {
                queueFamilyIndicies.transfer = queuefamilyIndex;
            }

            if (queuefamily.queueCount > 0 && queuefamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
            {
                queueFamilyIndicies.compute = queuefamilyIndex;
            }

            ++queuefamilyIndex;
        }

        return queueFamilyIndicies;
    }

    bool VulkanDevice::Builder::checkPhysicalDeviceExtensionSupport(VkPhysicalDevice const physicalDevice, std::vector<const char*> const requiredDeviceExtensions) const
    {
        uint32_t extensionCount{ 0 };
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

        if (extensionCount == 0)
        {
            return false;
        }

        std::vector<VkExtensionProperties> deviceExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, deviceExtensions.data());

        for (const auto& requiredDeviceExtension : requiredDeviceExtensions)
        {
            bool hasExtension = false;
            for (const auto& deviceExtension : deviceExtensions)
            {
                if (strcmp(requiredDeviceExtension, deviceExtension.extensionName) == 0)
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

    bool VulkanDevice::Builder::checkPhysicalDeviceSwapchainSupport(VkPhysicalDevice const physicalDevice, IVulkanSurface const *surface) const
    {
        uint32_t formatCount{ 0 };
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface->getSurface(), &formatCount, nullptr);

        uint32_t presentationCount{ 0 };
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface->getSurface(), &presentationCount, nullptr);

        if (formatCount == 0 || presentationCount == 0)
        {
            return false;
        }

        return true;
    }
}
