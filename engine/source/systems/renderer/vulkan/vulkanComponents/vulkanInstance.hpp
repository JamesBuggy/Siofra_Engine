#pragma once

#include <vulkan/vulkan.h>

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
        VulkanInstance();

        /**
         * @brief VulkanInstance constructor
         */
        VulkanInstance(VkInstance instance);
        
        /**
         * @brief VulkanInstance destructor
         */
        ~VulkanInstance();

        /**
         * @brief Destroy the vulkan instance handle
         */
        void destroy();

        /**
         * @brief Get the vulkan instance handle
         * 
         * @returns The vulkan instance handle
         */
        VkInstance getInstance();

    private:
        /**
         * @brief The vulkan instance handle
         */
        VkInstance instance;
    };
}
