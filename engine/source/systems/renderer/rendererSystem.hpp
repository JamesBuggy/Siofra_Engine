#pragma once

#include <memory>
#include "core/logging.hpp"
#include "core/assertions.hpp"
#include "systems/events/ieventSystem.hpp"
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
         * @param eventSystem Event system reference
         */
        RendererSystem(siofraEngine::platform::IWindow &window, systems::IEventSystem & eventSystem);

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

        /**
         * @brief Create a shader pipeline. Triggered by a CREATE_SHADER event broadcast
         * 
         * @param payload Payload describing the shader pipeline to create
         */
        void createShader(EventPayload payload);

        /**
         * @brief Create a material. Triggered by a CREATE_MATERIAL event broadcast
         * 
         * @param payload Payload describing the material to create
         */
        void createMaterial(EventPayload payload);
    };
}
