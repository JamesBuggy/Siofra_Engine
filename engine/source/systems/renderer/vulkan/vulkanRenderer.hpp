#pragma once

#include "core/logging.hpp"
#include "systems/renderer/irendererBackend.hpp"
#include "platform/iwindow.hpp"
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
         * 
         * @param window Window to be rendered to
         */
        VulkanRenderer(siofraEngine::platform::IWindow &window);

        /**
         * @brief VulkanRenderer destructor
         */
        ~VulkanRenderer();

    private:
        /**
         * @brief The vulkan instance
         */
        VulkanInstance instance;
    
    };
}
