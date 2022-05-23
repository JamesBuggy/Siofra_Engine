#pragma once

#include "core/logging.hpp"
#include "systems/renderer/irendererBackend.hpp"
#include "platform/window.hpp"
#include "systems/renderer/vulkan/vulkanComponents/builders/vulkanInstanceBuilder.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Renderer which uses the Vulkan graphics API
     */
    class VulkanRenderer : public IRendererBackend
    {
    public:
        /**
         * @brief VulkanRenderer constructor
         */
        VulkanRenderer(siofraEngine::platform::Window &window);

    private:
        /**
         * @brief The vulkan instance
         */
        VulkanInstance instance;
    
    };
}
