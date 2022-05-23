#pragma once

#include <memory>
#include "core/logging.hpp"
#include "core/assertions.hpp"
#include "systems/renderer/irendererBackend.hpp"
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
         * @brief Renderer backend
         */
        std::unique_ptr<IRendererBackend> rendererBackend{ };

        /**
         * @brief Create correct renderer backend based on the given window flags
         * 
         * @param window Window to be rendered to
         */
        static std::unique_ptr<IRendererBackend> createRendererBackend(siofraEngine::platform::Window &window);
    };
}
