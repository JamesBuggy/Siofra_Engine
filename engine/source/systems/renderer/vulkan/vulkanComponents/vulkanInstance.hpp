#pragma once

#include <vulkan/vulkan.h>
#include "core/logging.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Maintains a vulkan instance handle
     */
    class VulkanInstance
    {
    public:
        /**
         * @brief VulkanInstance builder
         */
        class Builder;

        /**
         * @brief VulkanInstance default constructor
         */
        VulkanInstance() = default;

        /**
         * @brief VulkanInstance constructor
         * 
         * @param instance VkInstance handle
         * @param debugMessenger Instance debug messenger
         */
        VulkanInstance(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger);

        /**
         * @brief Destroy the vulkan instance handle
         */
        void destroy();

        /**
         * @brief Get the vulkan instance handle
         * 
         * @returns The vulkan instance handle
         */
        VkInstance getInstance() const noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept;

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
         * @brief Instance debug messenger
         */
        VkDebugUtilsMessengerEXT debugMessenger{ VK_NULL_HANDLE };
    };
}
