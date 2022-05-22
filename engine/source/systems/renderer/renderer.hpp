#pragma once

#include <memory>
#include "core/logging.hpp"
#include "core/assertions.hpp"
#include "systems/renderer/irendererImpl.hpp"
#include "systems/renderer/vulkan/vulkanRenderer.hpp"
#include "platform/window.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Renderer system. Renders scenes to the window
     */
    class Renderer
    {
    public:
        /**
         * @brief Wraps plaftorm specific window logic
         * 
         * @param window Window to be rendered to
         */
        Renderer(siofraEngine::platform::Window &window);

    private:
        /**
         * @brief Renderer backend implementation
         */
        std::unique_ptr<IRendererImpl> rendererBackend{ };

        /**
         * @brief Create correct renderer backend based on the given window flags
         * 
         * @param windowFlags Flags used to determine the correct renderer backend
         */
        static std::unique_ptr<IRendererImpl> createRendererBackend(siofraEngine::platform::WindowFlags windowFlags);
    };
}
