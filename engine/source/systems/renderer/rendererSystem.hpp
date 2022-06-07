#pragma once

#include <memory>
#include "core/logging.hpp"
#include "core/assertions.hpp"
#include "systems/renderer/irendererBackend.hpp"
#include "systems/renderer/vulkan/vulkanRenderer.hpp"
#include "platform/iwindow.hpp"

namespace siofraEngine::systems
{
    /**
     * @brief Renderer system. Renders scenes to the window
     */
    class RendererSystem
    {
    public:
        /**
         * @brief Wraps plaftorm specific window logic
         * 
         * @param window Window to be rendered to
         */
        RendererSystem(siofraEngine::platform::IWindow &window);

        /**
         * @brief Draw current frame
         */
        void draw();

    private:
        /**
         * @brief Renderer backend
         */
        std::unique_ptr<IRendererBackend> rendererBackend{ };

        /**
         * @brief Create correct renderer backend based on the given window flags
         * 
         * @param window Window to be rendered to
         * @returns Renderer backend
         */
        static std::unique_ptr<IRendererBackend> createRendererBackend(siofraEngine::platform::IWindow &window);
    };
}
