#pragma once

#include "systems/renderer/vulkan/vulkanComponents/ivulkanSwapchain.hpp"
#include "systems/renderer/vulkan/vulkanComponents/ivulkanDevice.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Maintains a vulkan swapchain handle
     */
    class VulkanSwapchain : public IVulkanSwapchain
    {
    public:
        /**
         * @brief VulkanSwapchain builder
         */
        class Builder;

        /**
         * @brief VulkanSwapchain constructor
         * 
         * @param swapchain Swapchain handle
         * @param swapchainImageFormat Swapchain image format
         * @param swapchainExtents Swapchain extents
         * @param swapChainImages Swapchain images
         * @param device Device used to create the swapchain
         */
        VulkanSwapchain(VkSwapchainKHR swapchain, VkFormat swapchainImageFormat, VkExtent2D swapchainExtents, std::vector<std::unique_ptr<IVulkanImage>> swapChainImages, IVulkanDevice const * device);

        /**
         * @brief VulkanSwapchain copy constructor
         * 
         * @param other VulkanSwapchain to copy
         */
        VulkanSwapchain(VulkanSwapchain const &other) = delete;

        /**
         * @brief VulkanSwapchain move constructor
         * 
         * @param other VulkanSwapchain to move
         */
        VulkanSwapchain(VulkanSwapchain &&other) noexcept;

        /**
         * @brief VulkanSwapchain destructor
         */
        ~VulkanSwapchain();

        /**
         * @brief VulkanSwapchain copy assignment
         * 
         * @param other VulkanSwapchain to copy
         */
        VulkanSwapchain& operator=(const VulkanSwapchain &other) = delete;

        /**
         * @brief VulkanSwapchain move assignment
         * 
         * @param other VulkanSwapchain to move
         */
        VulkanSwapchain& operator=(VulkanSwapchain &&other) noexcept;

        /**
         * @brief Check if the wrapped handle is initialized
         * 
         * @returns True if the wrapped handle is intialized, otherwise false
         */
        operator bool() const noexcept override;

        /**
         * @brief Get swapchain handle
         */
        VkSwapchainKHR getSwapchain() const noexcept override;

        /**
         * @brief Get swapchain image format
         */
        VkFormat getImageFormat() const noexcept override;

        /**
         * @brief Get swapchain extents
         */
        VkExtent2D getExtents() const noexcept override;

        /**
         * @brief Get swapchain images
         */
        std::vector<std::unique_ptr<IVulkanImage>> const & getSwapchainImages() const noexcept override;

    private:
        /**
         * @brief Vulkan swapchain handle
         */
        VkSwapchainKHR swapchain{ VK_NULL_HANDLE };

        /**
         * @brief Swapchain image format
         */
        VkFormat swapchainImageFormat{ VK_FORMAT_UNDEFINED };

        /**
         * @brief Swapchain extents
         */
        VkExtent2D swapchainExtents{ 0, 0 };

        /**
         * @brief Swapchain images
         */
        std::vector<std::unique_ptr<IVulkanImage>> swapChainImages{ };

        /**
         * @brief Device used to create the swapchain
         */
        IVulkanDevice const * device{ nullptr };
    };
}
