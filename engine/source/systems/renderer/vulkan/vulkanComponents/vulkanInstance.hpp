#pragma once

#include "core/logging.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanInstance.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Maintains a vulkan instance handle
     */
    class VulkanInstance : public IVulkanInstance
    {
    public:
        /**
         * @brief VulkanInstance builder
         */
        class Builder;

        /**
         * @brief VulkanInstance constructor
         * 
         * @param instance VkInstance handle
         * @param debugMessenger Instance debug messenger handle
         */
        VulkanInstance(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger);

        /**
         * @brief VulkanInstance copy constructor
         * 
         * @param other VulkanInstance to copy
         */
        VulkanInstance(VulkanInstance const &other) = delete;

        /**
         * @brief VulkanInstance move constructor
         * 
         * @param other VulkanInstance to move
         */
        VulkanInstance(VulkanInstance &&other) noexcept;

        /**
         * @brief VulkanInstance destructor
         */
        ~VulkanInstance();

        /**
         * @brief VulkanInstance copy assignment
         * 
         * @param other VulkanInstance to copy
         */
        VulkanInstance& operator=(const VulkanInstance &other) = delete;

        /**
         * @brief VulkanInstance move assignment
         * 
         * @param other VulkanInstance to move
         */
        VulkanInstance& operator=(VulkanInstance &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;

        /**
         * @brief Get the vulkan instance handle
         * 
         * @returns The vulkan instance handle
         */
        VkInstance getInstance() const noexcept override;

        /**
         * @brief Log validation layer messages
         * 
         * @param messageSeverity Message severity
         * @param messageType MEssage type
         * @param pCallbackData Callback data
         * @param pUserData User data
         */
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
        {
            if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
            {
                SE_LOG_WARNING(pCallbackData->pMessage);
            }
            return VK_FALSE;
        }

    private:
        /**
         * @brief The vulkan instance handle
         */
        VkInstance instance{ VK_NULL_HANDLE };

        /**
         * @brief Instance debug messenger handle
         */
        VkDebugUtilsMessengerEXT debugMessenger{ VK_NULL_HANDLE };
    };
}
