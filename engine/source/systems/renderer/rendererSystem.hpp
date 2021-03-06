#pragma once

#include <memory>
#include "core/ecs/scene.hpp"
#include "platform/iwindow.hpp"
#include "systems/events/ieventSystem.hpp"
#include "systems/renderer/irendererBackend.hpp"
#include "systems/renderer/common/models.hpp"

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
         * @param eventSystem Event system
         */
        RendererSystem(platform::IWindow &window, IEventSystem * const eventSystem);

        /**
         * @brief Draw current frame
         * 
         * @param scene The ECS scene to render
         */
        void draw(core::Scene * scene);

    private:
        /**
         * @brief Renderer backend
         */
        std::unique_ptr<IRendererBackend> rendererBackend{ };

        /**
         * @brief View projection matrices
         */
        ViewProjection viewProjection{ };

        /**
         * @brief Create correct renderer backend based on the given window flags
         * 
         * @param window Window to be rendered to
         * @returns Renderer backend
         */
        static std::unique_ptr<IRendererBackend> createRendererBackend(platform::IWindow &window);

        /**
         * @brief Create a shader pipeline. Triggered by a CREATE_SHADER event broadcast
         * 
         * @param payload Payload describing the shader pipeline to create
         */
        void createShader(EventPayload payload) const;

        /**
         * @brief Create a material. Triggered by a CREATE_MATERIAL event broadcast
         * 
         * @param payload Payload describing the material to create
         */
        void createMaterial(EventPayload payload) const;

        /**
         * @brief Create a model. Triggered by a CREATE_MODEL event broadcast
         * 
         * @param payload Payload describing the model to create
         */
        void createModel(EventPayload payload) const;
    };
}
